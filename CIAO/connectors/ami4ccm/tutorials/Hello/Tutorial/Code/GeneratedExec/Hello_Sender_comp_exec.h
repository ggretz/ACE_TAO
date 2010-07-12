// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v1.7.9
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// C:\ACE\latest\ACE_wrappers\TAO\TAO_IDL\be\be_codegen.cpp:1265

#ifndef CIAO_HELLO_SENDER_COMP_EXEC_Y9ZN36_H_
#define CIAO_HELLO_SENDER_COMP_EXEC_Y9ZN36_H_


#include "Hello_Sender_compEC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/LocalObject.h"

namespace CIAO_Hello_Sender_comp_Impl
{
  
  class  Sender_comp_exec_i
    : public virtual Sender_comp_Exec,
      public virtual ::CORBA::LocalObject
  {
  public:
    Sender_comp_exec_i (void);
    virtual ~Sender_comp_exec_i (void);
    
    //@{
    /** Supported operations and attributes. */
    
    //@}
    
    //@{
    /** Component attributes and port operations. */
    
    //@}
    
    //@{
    /** Operations from Components::SessionComponent. */
    
    virtual void set_session_context (::Components::SessionContext_ptr ctx);
    
    virtual void configuration_complete (void);
    
    virtual void ccm_activate (void);
    virtual void ccm_passivate (void);
    virtual void ccm_remove (void);
    //@}
  
  private:
    ::Hello::CCM_Sender_comp_Context_var ciao_context_;
  };
  
  extern "C"  ::Components::EnterpriseComponent_ptr
  create_Hello_Sender_comp_Impl (void);
}

#endif /* ifndef */