
// Auto Genrated C++ file by newton CLI
#include "../include/url.h"

int main(int argc, char *argv[])
{

  /*essential */
  crow::SimpleApp *app = new crow::SimpleApp();
  V::Util *util = new V::Util();
  std::mutex mtx;
  std::unordered_set<crow::websocket::connection *> users;

  V::init_web_socket(app, util, users, mtx);//web socket should be first here otherwise it would not work
  /*url mapping*/
  V::map_url(app, util);

  /*REST API*/
  V::init_api(app);

  /*setting up port the server will run on*/
  char *port = getenv("PORT");
  uint16_t iport = static_cast<uint16_t>(port ? std::stoi(port) : 8080);
  app->port(iport).multithreaded().run();

  /*cleaning things up*/
  delete app;
  delete util;
  app = nullptr;
  util = nullptr;

  /*end of the program*/
  return 0;
};
