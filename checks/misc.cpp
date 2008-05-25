#include <iostream>
#include <vector>
#include <string>
#include <botan/signed_obj.h>

#include <botan/pipe.h>
#include <botan/hex.h>
#include <fstream>
using namespace Botan;




void strip_comments(std::string& line)
   {
   if(line.find('#') != std::string::npos)
      line = line.erase(line.find('#'), std::string::npos);
   }

void strip_newlines(std::string& line)
   {
   while(line.find('\n') != std::string::npos)
      line = line.erase(line.find('\n'), 1);
   }

void strip_newlines_windows(std::string& line)
   {
   while(line.find('\r') != std::string::npos)
   	{
//      line[line.find('\r')]='\n';
      line = line.erase(line.find('\r'), 1);
   	}
   }


/* Strip comments, whitespace, etc */
void strip(std::string& line)
   {
   strip_comments(line);

   while(line.find('\r') != std::string::npos)
      line = line.erase(line.find('\r'), 1);

//   while(line.find('\n') != std::string::npos)
//     line = line.erase(line.find('\n'), 1);

   while(line.find(' ') != std::string::npos)
      line = line.erase(line.find(' '), 1);

   while(line.find('\t') != std::string::npos)
      line = line.erase(line.find('\t'), 1);
   }


SecureVector<byte> decode_hex(const std::string& in)
   {
   SecureVector<byte> result;

   try {
      Botan::Pipe pipe(Botan::create_shared_ptr<Botan::Hex_Decoder>());
      pipe.process_msg(in);
      result = pipe.read_all();
   }
   catch(std::exception& e)
      {
      result.destroy();
      }
   return result;
   }

std::string hex_encode(const byte in[], u32bit len)
   {
   Botan::Pipe pipe(Botan::create_shared_ptr<Botan::Hex_Encoder>());
   pipe.process_msg(in, len);
   return pipe.read_all_as_string();
   }

std::vector<std::string> parse(const std::string& line)
   {
   const char DELIMITER = ':';
   std::vector<std::string> substr;
   std::string::size_type start = 0, end = line.find(DELIMITER);
   while(end != std::string::npos)
      {
      substr.push_back(line.substr(start, end-start));
      start = end+1;
      end = line.find(DELIMITER, start);
      }
   if(line.size() > start)
      substr.push_back(line.substr(start));
   while(substr.size() <= 4) // at least 5 substr, some possibly empty
      substr.push_back("");

   return substr;
   }

