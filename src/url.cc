#include "../include/url.h"

namespace V
{
    void init_api(crow::SimpleApp *app)
    {
        CROW_ROUTE((*app), "/api/").methods(crow::HTTPMethod::Post, crow::HTTPMethod::Get)([](const crow::request &req, crow::response &res)
                                                                                           {
      std::string method=crow::method_name(req.method);
      res.set_header("Content-Type","text/plain");
      res.write(method+" api");
      res.end(); });
    }
    void init_web_socket(crow::SimpleApp *app, V::Util *util, std::unordered_set<crow::websocket::connection *>&users, std::mutex &mtx)
    {

       /*web socket connection*/
        CROW_ROUTE((*app), "/ws")
            .websocket()
            .onopen([&users, &mtx](crow::websocket::connection &conn)
                    {
                std::lock_guard<std::mutex> _(mtx);users.insert(&conn); })
            .onclose([&users, &mtx](crow::websocket::connection &conn, const std::string &reason)

                     {std::lock_guard<std::mutex>_(mtx);users.erase(&conn); })
            .onmessage([&users, &mtx](crow::websocket::connection & /*conn*/, const std::string &data, bool is_binary)
                       {
    std::lock_guard<std::mutex>_(mtx);
    for(const auto user:users)
    {
      if(is_binary)
      {
        user->send_binary(data);
      }else
      {        
        user->send_text(data);
      };
      
    } });
    }
    void map_url(crow::SimpleApp *app, V::Util *util)
    {
      /*chat url mapping*/
        CROW_ROUTE((*app), "/chat")
        (
            [&util](const crow::request &req, crow::response &res)
            {
                util->send_html(res, "chat.html");
            });
            
        CROW_ROUTE((*app), "/music")
        (
            [&util](const crow::request &req, crow::response &res)
            {
                util->send_music(res, "index.html");
            });

        /*url mapping*/
        CROW_ROUTE((*app), "/")
        ([&util](const crow::request &req, crow::response &res)

         { util->send_html(res, "index.html"); });
        CROW_ROUTE((*app), "/<string>")
        ([&util](const crow::request &req, crow::response &res, const std::string &file_name)

         { util->send_html(res, file_name); });

        CROW_ROUTE((*app), "/css/<string>")
        ([&util](const crow::request &req, crow::response &res, const std::string &file_name)

         { util->send_style(res, file_name); });
        CROW_ROUTE((*app), "/images/<string>")
        ([&util](const crow::request &req, crow::response &res, const std::string &file_name)

         { util->send_images(res, file_name); });

        CROW_ROUTE((*app), "/images/avatar/<string>")
        ([&util](const crow::request &req, crow::response &res, const std::string &file_name)

         { util->send_images(res, "avatar/" + file_name); });
        CROW_ROUTE((*app), "/scripts/<string>")
        ([&util](const crow::request &req, crow::response &res, const std::string &file_name)

         { util->send_scripts(res, file_name); });

        CROW_ROUTE((*app), "/fonts/<string>")
        ([&util](const crow::request &req, crow::response &res, const std::string &file_name)

         { util->send_fonts(res, file_name); });

        CROW_ROUTE((*app), "/videos/<string>")
        ([&util](const crow::request &req, crow::response &res, const std::string &file_name)

         { util->send_videos(res, file_name); });
    };

}