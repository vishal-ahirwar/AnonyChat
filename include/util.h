#ifndef UTIL__
#define UTIL__
#include "../include/crow_all.h"
namespace V
{

    class Util
    {
        private:
            void send_file(crow::response&res,const std::string&file_name,const std::string&content_type);

        public:

            void send_html(crow::response&res,const std::string&file_name);
            void send_style(crow::response&res,const std::string&file_name);
            void send_scripts(crow::response&res,const std::string&file_name);

            void send_images(crow::response&res,const std::string&file_name);
            void send_fonts(crow::response&res,const std::string&file_name);
            void send_videos(crow::response&res,const std::string&file_name);
            void send_docs(crow::response&res,const std::string&file_name);

    };
};

#endif