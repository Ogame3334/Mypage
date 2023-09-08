#include "mypage_manage_works.h"

using namespace mypage::manage;

// Add definition of your processing function here

void works::direct( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const{
    bool loginState = false;
    auto sessionHolder = req->getSession();
    if(sessionHolder->find("loginState"))
    {
        loginState = sessionHolder->getOptional<bool>("loginState").value_or(false);
    }
    
    if(loginState){
        auto res = HttpResponse::newHttpViewResponse("manage_works.csp");

        callback(res);
        return;
    }
    else{
        auto res = HttpResponse::newRedirectionResponse("/mypage/manage/login");
        req->session()->insert("login_redirect_path", req->getPath());
        callback(res);
    }
}
void works::add( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const{
    bool loginState = false;
    auto sessionHolder = req->getSession();
    if(sessionHolder->find("loginState"))
    {
        loginState = sessionHolder->getOptional<bool>("loginState").value_or(false);
    }
    
    if(loginState){
        HttpViewData viewData{};
        viewData.insert("isAdded", false);
        auto res = HttpResponse::newHttpViewResponse("manage_works_add.csp", viewData);
        
        callback(res);
        return;
    }
    else{
        auto res = HttpResponse::newRedirectionResponse("/mypage/manage/login");
        req->session()->insert("login_redirect_path", req->getPath());
        callback(res);
    }
}
void works::add_submit( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const{
    bool loginState = false;
    auto sessionHolder = req->getSession();
    if(sessionHolder->find("loginState"))
    {
        loginState = sessionHolder->getOptional<bool>("loginState").value_or(false);
    }
    
    if(loginState){
        std::string title = req->getParameter("title");
        std::string detail = req->getParameter("detail");

        std::cout << title << std::endl;

        auto res = HttpResponse::newRedirectionResponse("/mypage/manage/works/add/succeeded");

        callback(res);
        return;
    }
    else{
        auto res = HttpResponse::newHttpResponse();
        res->setStatusCode(k403Forbidden);
        res->setContentTypeCode(CT_TEXT_HTML);
        res->setBody("Your request will not be granted.");
        
        callback(res);
    }
}
void works::add_succeeded( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const{
    bool loginState = false;
    auto sessionHolder = req->getSession();
    if(sessionHolder->find("loginState"))
    {
        loginState = sessionHolder->getOptional<bool>("loginState").value_or(false);
    }
    
    if(loginState){
        HttpViewData viewData{};
        viewData.insert("isAdded", true);
        auto res = HttpResponse::newHttpViewResponse("manage_works_add.csp", viewData);

        callback(res);
        return;
    }
    else{
        auto res = HttpResponse::newRedirectionResponse("/mypage/manage/login");
        req->session()->insert("login_redirect_path", req->getPath());
        callback(res);
    }
}
void works::edit( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const{
    bool loginState = false;
    auto sessionHolder = req->getSession();
    if(sessionHolder->find("loginState"))
    {
        loginState = sessionHolder->getOptional<bool>("loginState").value_or(false);
    }
    
    if(loginState){
        auto res = HttpResponse::newHttpResponse();
        res->setStatusCode(k200OK);
        res->setContentTypeCode(CT_TEXT_HTML);
        res->setBody("Hi, I'm works edit.");
        
        callback(res);
        return;
    }
    else{
        auto res = HttpResponse::newRedirectionResponse("/mypage/manage/login");
        req->session()->insert("login_redirect_path", req->getPath());
        callback(res);
    }
}