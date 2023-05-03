#ifndef __URL__
#define __URL__
#include "../include/util.h"
#include <memory>
#include <mutex>
#include <unordered_set>

namespace V
{
        void map_url(crow::SimpleApp *app, V::Util *util);
        void init_web_socket(crow::SimpleApp *app, V::Util *util,std::unordered_set<crow::websocket::connection *>&users,std::mutex &mtx);
        void init_api(  crow::SimpleApp *app );
}
#endif