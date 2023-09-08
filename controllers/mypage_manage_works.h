#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace mypage
{
namespace manage
{
class works : public drogon::HttpController<works>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(works::get, "/{2}/{1}", Get); // path is /mypage/manage/works/{arg2}/{arg1}
    // METHOD_ADD(works::your_method_name, "/{1}/{2}/list", Get); // path is /mypage/manage/works/{arg1}/{arg2}/list
    // ADD_METHOD_TO(works::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    METHOD_ADD(works::direct, "", Get);
    METHOD_ADD(works::add, "/add", Get);
    METHOD_ADD(works::add_submit, "/add", Post);
    METHOD_ADD(works::add_succeeded, "/add/succeeded", Get);
    METHOD_ADD(works::edit, "/edit", Get);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;

    void direct( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;
    void add( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;
    void add_submit( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;
    void add_succeeded( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;
    void edit( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;

  private:
    std::vector<std::string> enabledExtension;
  public:
    works():
    enabledExtension({"gif", "png", "jpg", "jpeg", "ico", "webp", "mp4", "mp3", "wav"})
    {}
};
}
}
