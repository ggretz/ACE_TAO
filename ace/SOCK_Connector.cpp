// SOCK_Connector.cpp
// $Id$


#define ACE_BUILD_DLL
#include "ace/SOCK_Connector.h"
#include "ace/Handle_Set.h"
#include "ace/INET_Addr.h"

ACE_ALLOC_HOOK_DEFINE(ACE_SOCK_Connector)

void
ACE_SOCK_Connector::dump (void) const
{
  ACE_TRACE ("ACE_SOCK_Connector::dump");
}

// Actively connect and produce a new ACE_SOCK_Stream if things go well...

int
ACE_SOCK_Connector::connect (ACE_SOCK_Stream &new_stream, 
			     const ACE_Addr &remote_sap, 
			     ACE_Time_Value *timeout,
			     const ACE_Addr &local_sap,
			     int reuse_addr,
			     int /* flags */,
			     int /* perms */,
			     int protocol_family, 
			     int protocol)
{
  ACE_TRACE ("ACE_SOCK_Connector::connect");
  int result = 0;

  // Only open a new socket if we don't already have a valid handle.
  if (new_stream.get_handle () == ACE_INVALID_HANDLE)
    {
      if (ACE_SOCK::open (SOCK_STREAM, protocol_family, 
			  protocol, reuse_addr) == -1)
	return -1;
    }
  else // Borrow the handle from the NEW_STREAM. 
    this->set_handle (new_stream.get_handle ());

  sockaddr *raddr = (sockaddr *) remote_sap.get_addr ();
  size_t rsize  = remote_sap.get_size ();

  if (&local_sap != &ACE_Addr::sap_any)
    {
      sockaddr *laddr = (sockaddr *) local_sap.get_addr ();
      size_t size = local_sap.get_size ();
      result = ACE_OS::bind (this->get_handle (), laddr, size);

      if (result == -1)
	{
	  this->close ();
	  return -1;
	}
    }

  // Enable non-blocking, if required.
  if (timeout != 0)
    {
      if (this->enable (ACE_NONBLOCK) == -1)
	result = -1;
      
      if (ACE_OS::connect (this->get_handle (), raddr, rsize) == -1)
	{
	  result = -1;

	  // Check whether the connection is in progress.
	  if (errno == EINPROGRESS || errno == EWOULDBLOCK)
	    {
	      // This expression checks if we were polling.
	      if (timeout->sec () == 0 && timeout->usec () == 0)
		errno = EWOULDBLOCK;
	      // Wait synchronously
	      else if (this->complete (new_stream, 0, timeout) != -1)
		return 0;
	    }
	}
    }
  // Do a blocking connect.
  else if (ACE_OS::connect (this->get_handle (), raddr, rsize) == -1)
    result = -1;

  // EISCONN is treated specially since this routine may be used to check 
  // if we are already connected.
  if (result != -1 || errno == EISCONN)
    {
      // If everything succeeded transfer ownership to <new_stream>.
      new_stream.set_handle (this->get_handle ());
      this->set_handle (ACE_INVALID_HANDLE);
    }
  else if (!(errno == EWOULDBLOCK || errno == ETIMEDOUT))
    {
      // If things have gone wrong, close down and return an error.
      this->close ();
      new_stream.set_handle (ACE_INVALID_HANDLE);
    }
  return result;
}

// Try to complete a non-blocking connection.

int
ACE_SOCK_Connector::complete (ACE_SOCK_Stream &new_stream,
			      ACE_Addr *remote_sap,
			      ACE_Time_Value *tv)
{
  ACE_TRACE ("ACE_SOCK_Connector::complete");
#if defined (ACE_HAS_BROKEN_NON_BLOCKING_CONNECTS)
  ACE_OS::sleep (0);
#endif /* ACE_HAS_BROKEN_NON_BLOCKING_CONNECTS */
  ACE_HANDLE h = ACE::handle_timed_complete (this->get_handle (), tv);

  if (h == ACE_INVALID_HANDLE)
    {
      this->close ();
      return -1;
    }
  else 	  // We've successfully connected!
    {
      if (remote_sap != 0)
	{
	  int len;

	  len = remote_sap->get_size ();
	  sockaddr *addr = (sockaddr *) remote_sap->get_addr ();

	  if (ACE_OS::getpeername (h, addr, &len) == -1)
	    {
	      this->close ();
	      return -1;
	    }
	}

      // Transfer ownership.
      new_stream.set_handle (this->get_handle ());

      // Start out with non-blocking disabled on the <new_stream>.
      new_stream.disable (ACE_NONBLOCK);

      this->set_handle (ACE_INVALID_HANDLE);
      return 0;
    }
}


