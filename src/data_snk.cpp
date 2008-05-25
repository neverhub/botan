/*************************************************
* DataSink Source File                           *
* (C) 1999-2007 The Botan Project                *
*************************************************/

#include <botan/data_snk.h>
#include <fstream>

namespace Botan {

/*************************************************
* Write to a stream                              *
*************************************************/
void DataSink_Stream::write(const byte out[], u32bit length)
   {
   sink->write(reinterpret_cast<const char*>(out), length);
   if(!sink->good())
      throw Stream_IO_Error("DataSink_Stream: Failure writing to " + fsname);
   }

/*************************************************
* DataSink_Stream Constructor                    *
*************************************************/
DataSink_Stream::DataSink_Stream(const SharedPtrConverter<std::ostream>& stream) : fsname("std::ostream")
   {
   sink = stream.get_shared();
   owns = false;
   }

/*************************************************
* DataSink_Stream Constructor                    *
*************************************************/
DataSink_Stream::DataSink_Stream(const std::string& file,
                                 bool use_binary) : fsname(file)
   {
   if(use_binary)
      sink = std::tr1::shared_ptr<std::ostream>(new std::ofstream(fsname.c_str(), std::ios::binary));
   else
      sink = std::tr1::shared_ptr<std::ostream>(new std::ofstream(fsname.c_str()));

   if(!sink->good())
      throw Stream_IO_Error("DataSink_Stream: Failure opening " + fsname);
   owns = true;
   }

/*************************************************
* DataSink_Stream Destructor                     *
*************************************************/
DataSink_Stream::~DataSink_Stream()
   {
    sink.reset();
   }

}
