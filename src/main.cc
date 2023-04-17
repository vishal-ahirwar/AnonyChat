
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

int main(int argc, char *argv[])
{
  
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")
    ([](const crow::request&req, crow::response&res)
     
     {
        send_file(res,"index.html","plain-text");
     }
     );
    char *port = getenv("PORT");
    uint16_t iport = static_cast<uint16_t>(port ? std::stoi(port) : 8080);
    app.port(iport).multithreaded().run();
    return 0;
};
