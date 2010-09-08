// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v1.8.1
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
// be/be_codegen.cpp:1333

#include "CIF_Component_exec.h"

namespace CIAO_CIF_CIF_Provider_Impl
{
  
  // TAO_IDL - Generated from
  // be/be_visitor_component/facet_exs.cpp:75
  //============================================================
  // Facet Executor Implementation Class: provide_cif_foo_exec_i
  //============================================================
  
  provide_cif_foo_exec_i::provide_cif_foo_exec_i (
        ::CIF::CCM_CIF_Provider_Context_ptr ctx)
    : ciao_context_ (
        ::CIF::CCM_CIF_Provider_Context::_duplicate (ctx))
  {
  }
  
  provide_cif_foo_exec_i::~provide_cif_foo_exec_i (void)
  {
  }
  
  // Operations from ::CIF::foo
  
  void
  provide_cif_foo_exec_i::do_foo (void)
  {
    /* Your code here. */
  }
  
  // TAO_IDL - Generated from
  // be/be_visitor_component/facet_exs.cpp:75
  //============================================================
  // Facet Executor Implementation Class: provide_cif_inherited_foo_exec_i
  //============================================================
  
  provide_cif_inherited_foo_exec_i::provide_cif_inherited_foo_exec_i (
        ::CIF::CCM_CIF_Provider_Context_ptr ctx)
    : ciao_context_ (
        ::CIF::CCM_CIF_Provider_Context::_duplicate (ctx))
  {
  }
  
  provide_cif_inherited_foo_exec_i::~provide_cif_inherited_foo_exec_i (void)
  {
  }
  
  // Operations from ::CIF::inherited_foo
  
  void
  provide_cif_inherited_foo_exec_i::do_foo (void)
  {
    /* Your code here. */
  }
  
  void
  provide_cif_inherited_foo_exec_i::do_inherited_foo (void)
  {
    /* Your code here. */
  }
  
  //============================================================
  // Component Executor Implementation Class: CIF_Provider_exec_i
  //============================================================
  
  CIF_Provider_exec_i::CIF_Provider_exec_i (void)
  {
  }
  
  CIF_Provider_exec_i::~CIF_Provider_exec_i (void)
  {
  }
  
  // Supported operations and attributes.
  
  // Component attributes and port operations.
  
  ::CIF::CCM_foo_ptr
  CIF_Provider_exec_i::get_provide_cif_foo (void)
  {
    ACE_DEBUG ((LM_DEBUG, "CIF_Provider_exec_i::get_provide_cif_foo"));

    if ( ::CORBA::is_nil (this->ciao_provide_cif_foo_.in ()))
      {
        provide_cif_foo_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          provide_cif_foo_exec_i (
            this->ciao_context_.in ()),
          ::CIF::CCM_foo::_nil ());

        this->ciao_provide_cif_foo_ = tmp;
      }

    return
      ::CIF::CCM_foo::_duplicate (
        this->ciao_provide_cif_foo_.in ());
  }
  
  ::CIF::CCM_inherited_foo_ptr
  CIF_Provider_exec_i::get_provide_cif_inherited_foo (void)
  {
    ACE_DEBUG ((LM_DEBUG, "CIF_Provider_exec_i::get_provide_cif_inherited_foo"));

    if ( ::CORBA::is_nil (this->ciao_provide_cif_inherited_foo_.in ()))
      {
        provide_cif_inherited_foo_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          provide_cif_inherited_foo_exec_i (
            this->ciao_context_.in ()),
          ::CIF::CCM_inherited_foo::_nil ());

        this->ciao_provide_cif_inherited_foo_ = tmp;
      }

    return
      ::CIF::CCM_inherited_foo::_duplicate (
        this->ciao_provide_cif_inherited_foo_.in ());
  }

  // Operations from Components::SessionComponent.
  void
  CIF_Provider_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::CIF::CCM_CIF_Provider_Context::_narrow (ctx);

    if ( ::CORBA::is_nil (this->ciao_context_.in ()))
      {
        throw ::CORBA::INTERNAL ();
      }
  }

  void
  CIF_Provider_exec_i::configuration_complete (void)
  {
    /* Your code here. */
  }

  void
  CIF_Provider_exec_i::ccm_activate (void)
  {
    /* Your code here. */
  }

  void
  CIF_Provider_exec_i::ccm_passivate (void)
  {
    /* Your code here. */
  }

  void
  CIF_Provider_exec_i::ccm_remove (void)
  {
    /* Your code here. */
  }

  extern "C"  ::Components::EnterpriseComponent_ptr
  create_CIF_CIF_Provider_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      CIF_Provider_exec_i);

    return retval;
  }
}

namespace CIAO_CIF_CIF_User_Impl
{
  //============================================================
  // Component Executor Implementation Class: CIF_User_exec_i
  //============================================================

  CIF_User_exec_i::CIF_User_exec_i (void)
  {
  }

  CIF_User_exec_i::~CIF_User_exec_i (void)
  {
  }

  // Supported operations and attributes.

  // Component attributes and port operations.

  // Operations from Components::SessionComponent.

  void
  CIF_User_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::CIF::CCM_CIF_User_Context::_narrow (ctx);

    if ( ::CORBA::is_nil (this->ciao_context_.in ()))
      {
        throw ::CORBA::INTERNAL ();
      }
  }

  void
  CIF_User_exec_i::configuration_complete (void)
  {
    /* Your code here. */
  }

  void
  CIF_User_exec_i::ccm_activate (void)
  {
    /* Your code here. */
  }

  void
  CIF_User_exec_i::ccm_passivate (void)
  {
    /* Your code here. */
  }

  void
  CIF_User_exec_i::ccm_remove (void)
  {
    /* Your code here. */
  }

  extern "C"  ::Components::EnterpriseComponent_ptr
  create_CIF_CIF_User_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      CIF_User_exec_i);

    return retval;
  }
}