#include "DAM_Map.h"
#include "ciao/CIAO_Config.h"
#include "ciao/CIAO_common.h"

ACE_RCSID (ExecutionManager,
           DAM_Map,
           "$Id$")

namespace CIAO
{
  namespace Execution_Manager
  {
    DAM_Map::DAM_Map (void)
      : map_ (CIAO_DEFAULT_MAP_SIZE)
    {
    }

    bool
    DAM_Map::is_plan_available (const ACE_CString &str)
    {
      if (this->map_.find (str) == 0)
        return true;

      return false;
    }

    ::Deployment::DomainApplicationManager_ptr
    DAM_Map::fetch_dam_reference (const ACE_CString &str)
    {
      if (!this->is_plan_available (str))
        return ::Deployment::DomainApplicationManager::_nil ();

      ::Deployment::DomainApplicationManager_var tmp;

      /// There should be duplicate when assigning a _var to an _var.
      int retval =  this->map_.find (str,
                                     tmp);

      if (CIAO::debug_level () > 10)
        {
          ACE_DEBUG ((LM_DEBUG,
                      "(%P|%t) CIAO_ExecutionManager: fetch_dam_reference, "
                      "result from find is [%d] \n",
                      retval));
        }

      return tmp._retn ();
    }


    bool
    DAM_Map::bind_dam_reference (
      const ACE_CString &str,
      ::Deployment::DomainApplicationManager_ptr dam)
    {
      int retval =
        this->map_.bind (str,
                         dam);

      if (retval != 0)
        return false;

      return true;
    }


    Deployment::DomainApplicationManagers *
    DAM_Map::get_dams (ACE_ENV_SINGLE_ARG_DECL)
    {
      CORBA::ULong sz =
        this->map_.current_size ();

      // Initialize the list of DomainApplication Managers
      Deployment::DomainApplicationManagers_var list;
      ACE_NEW_THROW_EX (list,
                        Deployment::DomainApplicationManagers (sz),
                        CORBA::NO_MEMORY());
      ACE_CHECK_RETURN (0);

      // Add the manager to the list
      list->length (sz);

      Iterator end =
        this->map_.end ();

      CORBA::ULong i = 0;

      for (Iterator b =
             this->map_.begin (); b != end; ++b)
        {
          list [i] =
            Deployment::DomainApplicationManager::_duplicate ((*b).int_id_.in ());

          ++i;
        }

      return list._retn ();
    }

    bool
    DAM_Map::unbind_dam (const ACE_CString &str)
    {
      int retval =
        this->map_.unbind (str);

      if (retval != 0)
        return false;

      return true;
    }
  }
}
