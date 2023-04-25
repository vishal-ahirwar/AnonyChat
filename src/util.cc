#include"../include/util.h"

namespace V
{

  void Util::send_file(crow::response&res,const std::string&file_name,const std::string&content_type)
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


  void Util::send_html(crow::response&res,const std::string&file_name)
  {
      this->send_file(res,file_name,"text/html");
  };

  void Util::send_style(crow::response&res,const std::string&file_name)
  {
      this->send_file(res,"css/"+file_name,"text/css");
  };

  void Util::send_scripts(crow::response&res,const std::string&file_name)
  {
      this->send_file(res,"scripts/"+file_name,"text/javascript");
  };

  void Util::send_images(crow::response&res,const std::string&file_name)
  {
      this->send_file(res,"images/"+file_name,"image/png");
  };

  void Util::send_fonts(crow::response&res,const std::string&file_name)
  {
      this->send_file(res,"fonts/"+file_name,"text/font");
  };

  void Util::send_videos(crow::response&res,const std::string&file_name)
  {
      this->send_file(res,"videos/"+file_name,"video/mp4");
  };

  void Util::send_docs(crow::response&res,const std::string&file_name)
  {
    this->send_file(res,"docs/"+file_name,"text/documents");
  }
}