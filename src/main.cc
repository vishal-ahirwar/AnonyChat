
// Auto Genrated C++ file by newton CLI
#include "../include/util.h"
#include <memory>
#include <mutex>
#include <unordered_set>

int main(int argc, char *argv[])
{

  crow::SimpleApp *app = new crow::SimpleApp();
  V::Util *util = new V::Util();
  std::mutex mtx;
  std::unordered_set<crow::websocket::connection *> users;

  CROW_ROUTE((*app), "/chat")
  (
      [&util](const crow::request &req, crow::response &res)
      {
        util->send_html(res, "chat.html");
      });
  CROW_ROUTE((*app), "/ws")
      .websocket()
      .onopen([&users, &mtx](crow::websocket::connection &conn)
              {
                std::lock_guard<std::mutex> _(mtx);
                users.insert(&conn);
              })
      .onclose([&users, &mtx](crow::websocket::connection &conn, const std::string &reason)
               {
    std::lock_guard<std::mutex>_(mtx);
    users.erase(&conn); })
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

  delete util;
  util = nullptr;
  char *port = getenv("PORT");
  uint16_t iport = static_cast<uint16_t>(port ? std::stoi(port) : 8080);
  app->port(iport).multithreaded().run();
  delete app;
  return 0;
};
