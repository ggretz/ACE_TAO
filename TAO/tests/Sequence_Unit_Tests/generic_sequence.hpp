#ifndef guard_TAO_generic_sequence_hpp
#define guard_TAO_generic_sequence_hpp
/**
 * @file
 *
 * @brief Implement the generic version of CORBA sequences.
 *
 * All CORBA sequences are based on this class template.  The
 * differences are encapsulated in a TRAITS template argument.
 *
 * $Id$
 *
 * @author Carlos O'Ryan
 */

#include "sequence_traits.hpp"

#include <algorithm>

namespace TAO
{
namespace details
{

template<class T, class TRAITS>
class generic_sequence
{
public:
  typedef T value_type;
  typedef TRAITS traits;

  generic_sequence()
    : maximum_(traits::default_maximum())
    , length_(0)
    , buffer_(traits::default_buffer_allocation())
    , release_(true)
  {
  }

  explicit generic_sequence(CORBA::ULong maximum)
    : maximum_(maximum)
    , length_(0)
    , buffer_(allocbuf(maximum_))
    , release_(true)
  {
  }

  generic_sequence(
      CORBA::ULong maximum,
      CORBA::ULong length,
      T * data,
      CORBA::Boolean release)
    : maximum_(maximum)
    , length_(length)
    , buffer_(data)
    , release_(release)
  {
  }

  generic_sequence(generic_sequence const & rhs)
    : maximum_(0)
    , length_(0)
    , buffer_(0)
    , release_(false)
  {
    generic_sequence tmp(rhs.maximum_);
    tmp.length_ = rhs.length_;
    std::copy(rhs.buffer_, rhs.buffer_ + rhs.length_, tmp.buffer_);
    swap(tmp);
  }

  generic_sequence & operator=(generic_sequence const & rhs)
  {
    generic_sequence tmp(rhs);
    swap(tmp);
    return * this;
  }

  ~generic_sequence()
  {
    if (release_)
    {
      freebuf(buffer_);
    }
  }

  inline CORBA::ULong maximum() const
  {
    return maximum_;
  }

  inline CORBA::Boolean release() const
  {
    return release_;
  }

  inline CORBA::ULong length() const
  {
    return length_;
  }

  void length(CORBA::ULong length)
  {
    if (length < maximum_ || length < length_)
    {
      length_ = length;
      return;
    }

    generic_sequence tmp(length); tmp.length_ = length;
    std::copy(buffer_, buffer_ + length_, tmp.buffer_);
    swap(tmp);
  }

  value_type const & operator[](CORBA::ULong i) const
  {
    traits::check_index(i, length_, maximum_, "operator[]() const");
    return buffer_[i];
  }

  value_type & operator[](CORBA::ULong i)
  {
    traits::check_index(i, length_, maximum_, "operator[]() non-const");
    return buffer_[i];
  }

  void replace(
      CORBA::ULong maximum,
      CORBA::ULong length,
      T * data,
      CORBA::Boolean release)
  {
    generic_sequence tmp(maximum, length, data, release);
    swap(tmp);
  }

  T const * get_buffer() const
  {
    if (buffer_ == 0)
    {
      buffer_ = allocbuf(maximum_);
    }
    return buffer_;
  }

  T * get_buffer(CORBA::Boolean orphan)
  {
    if (orphan && !release_)
    {
      return 0;
    }
    if (buffer_ == 0)
    {
      buffer_ = allocbuf(maximum_);
    }
    if (!orphan)
    {
      return buffer_;
    }

    generic_sequence tmp;
    swap(tmp);
    tmp.release_ = false;

    return tmp.buffer_;
  }

  void swap(generic_sequence & rhs) throw()
  {
    std::swap(maximum_, rhs.maximum_);
    std::swap(length_, rhs.length_);
    std::swap(buffer_, rhs.buffer_);
    std::swap(release_, rhs.release_);
  }

  static T * allocbuf(CORBA::ULong maximum)
  {
    return traits::allocbuf(maximum);
  }

  static void freebuf(T * buffer)
  {
    traits::freebuf(buffer);
  }

private:
  CORBA::ULong maximum_;
  CORBA::ULong length_;
  mutable T * buffer_;
  CORBA::Boolean release_;
};

} // namespace details
} // namespace CORBA

#endif // guard_TAO_generic_sequence_hpp
