
// Auto Genrated C++ file by newton CLI
#include "../include/crow_all.h"
void send_file(crow::response&res,const std::string&file_name,const std::string&content_type)
{
       std::ifstream in("public/"+file_name,std::ifstream::in);
        if(in)
        {
            std::ostringstream contens;
            contens<<in.rdbuf();
            in.close();
            res.set_header("Content-Type",content_type);
            res.write(contens.str());
        }else
        {
            res.code=404;
            res.write("Not found!\n");
        };

        res.end();
};


void send_html(crow::response&res,const std::string&file_name)
{
    send_file(res,file_name,"text/html");
};

void send_style(crow::response&res,const std::string&file_name)
{
    send_file(res,"css/"+file_name,"text/css");
};

void send_scripts(crow::response&res,const std::string&file_name)
{
    send_file(res,"scripts/"+file_name,"text/javascript");
};

void send_images(crow::response&res,const std::string&file_name)
{
    auto index=file_name.find(".");
    auto str=file_name.substr(index+1);
    printf("[message] : %s",str.c_str());
    if(str=="png")
    send_file(res,"images/"+file_name,"image/png");
    else
    send_file(res,"images/"+file_name,"image/jpg"); 
};

void send_fonts(crow::response&res,const std::string&file_name)
{
    send_file(res,"fonts/"+file_name,"text/font");
};

void send_videos(crow::response&res,const std::string&file_name)
{
    send_file(res,"videos/"+file_name,"video/mp4");
};

int main(int argc, char *argv[])
{
  
    crow::SimpleApp app;
        CROW_ROUTE(app, "/")
    ([](const crow::request&req, crow::response&res)
     
     {
       send_html(res,"index.html");
     }
     );
    CROW_ROUTE(app, "/<string>")
    ([](const crow::request&req, crow::response&res,const std::string&file_name)
     
     {
       send_html(res,file_name);
     }
     );

         CROW_ROUTE(app, "/css/<string>")
    ([](const crow::request&req, crow::response&res,const std::string&file_name)
     
     {
       send_style(res,file_name);
     }
     );
         CROW_ROUTE(app, "/images/<string>")
    ([](const crow::request&req, crow::response&res,const std::string&file_name)
     
     {
       send_images(res,file_name);
     }
     );

            CROW_ROUTE(app, "/images/avatar/<string>")
    ([](const crow::request&req, crow::response&res,const std::string&file_name)
     
     {
       send_images(res,"avatar/"+file_name);
     }
     );
         CROW_ROUTE(app, "/scripts/<string>")
    ([](const crow::request&req, crow::response&res,const std::string&file_name)
     
     {
       send_scripts(res,file_name);
     }
     );

         CROW_ROUTE(app, "/fonts/<string>")
    ([](const crow::request&req, crow::response&res,const std::string&file_name)
     
     {
       send_fonts(res,file_name);
     }
     );

     
         CROW_ROUTE(app, "/videos/<string>")
    ([](const crow::request&req, crow::response&res,const std::string&file_name)
     
     {
       send_videos(res,file_name);
     }
     );
     
    char *port = getenv("PORT");
    uint16_t iport = static_cast<uint16_t>(port ? std::stoi(port) : 8080);
    app.port(iport).multithreaded().run();
    return 0;
};
