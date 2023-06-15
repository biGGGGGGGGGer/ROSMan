// Generated by gencpp from file speedimu/imuspeed.msg
// DO NOT EDIT!


#ifndef SPEEDIMU_MESSAGE_IMUSPEED_H
#define SPEEDIMU_MESSAGE_IMUSPEED_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace speedimu
{
template <class ContainerAllocator>
struct imuspeed_
{
  typedef imuspeed_<ContainerAllocator> Type;

  imuspeed_()
    : pitch(0.0)
    , roll(0.0)
    , yaw(0.0)  {
    }
  imuspeed_(const ContainerAllocator& _alloc)
    : pitch(0.0)
    , roll(0.0)
    , yaw(0.0)  {
  (void)_alloc;
    }



   typedef float _pitch_type;
  _pitch_type pitch;

   typedef float _roll_type;
  _roll_type roll;

   typedef float _yaw_type;
  _yaw_type yaw;





  typedef boost::shared_ptr< ::speedimu::imuspeed_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::speedimu::imuspeed_<ContainerAllocator> const> ConstPtr;

}; // struct imuspeed_

typedef ::speedimu::imuspeed_<std::allocator<void> > imuspeed;

typedef boost::shared_ptr< ::speedimu::imuspeed > imuspeedPtr;
typedef boost::shared_ptr< ::speedimu::imuspeed const> imuspeedConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::speedimu::imuspeed_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::speedimu::imuspeed_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::speedimu::imuspeed_<ContainerAllocator1> & lhs, const ::speedimu::imuspeed_<ContainerAllocator2> & rhs)
{
  return lhs.pitch == rhs.pitch &&
    lhs.roll == rhs.roll &&
    lhs.yaw == rhs.yaw;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::speedimu::imuspeed_<ContainerAllocator1> & lhs, const ::speedimu::imuspeed_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace speedimu

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::speedimu::imuspeed_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::speedimu::imuspeed_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::speedimu::imuspeed_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::speedimu::imuspeed_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::speedimu::imuspeed_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::speedimu::imuspeed_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::speedimu::imuspeed_<ContainerAllocator> >
{
  static const char* value()
  {
    return "5cdafae0cb68983e8e8825adb0b735f2";
  }

  static const char* value(const ::speedimu::imuspeed_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x5cdafae0cb68983eULL;
  static const uint64_t static_value2 = 0x8e8825adb0b735f2ULL;
};

template<class ContainerAllocator>
struct DataType< ::speedimu::imuspeed_<ContainerAllocator> >
{
  static const char* value()
  {
    return "speedimu/imuspeed";
  }

  static const char* value(const ::speedimu::imuspeed_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::speedimu::imuspeed_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 pitch\n"
"float32 roll\n"
"float32 yaw\n"
;
  }

  static const char* value(const ::speedimu::imuspeed_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::speedimu::imuspeed_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.pitch);
      stream.next(m.roll);
      stream.next(m.yaw);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct imuspeed_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::speedimu::imuspeed_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::speedimu::imuspeed_<ContainerAllocator>& v)
  {
    s << indent << "pitch: ";
    Printer<float>::stream(s, indent + "  ", v.pitch);
    s << indent << "roll: ";
    Printer<float>::stream(s, indent + "  ", v.roll);
    s << indent << "yaw: ";
    Printer<float>::stream(s, indent + "  ", v.yaw);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SPEEDIMU_MESSAGE_IMUSPEED_H
