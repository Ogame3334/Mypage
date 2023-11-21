#include "manage.h"
#include "loginUtility.h"
#include <drogon/HttpClient.h>

// Add definition of your processing function here
void manage::manage_direct( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    bool loginState = false;
    auto sessionHolder = req->getSession();
    if(sessionHolder->find("loginState"))
    {
        loginState = sessionHolder->getOptional<bool>("loginState").value_or(false);
    }
    
    if(loginState){
        auto res = HttpResponse::newHttpViewResponse("manage_top.csp");
        callback(res);
        return;
    }
    else{
        auto res = HttpResponse::newRedirectionResponse("/manage/login");
        req->session()->insert("login_redirect_path", req->getPath());
        callback(res);
        return;
    }
}

void manage::manage_login( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    auto res = HttpResponse::newHttpViewResponse("manage_login.csp");
    
    callback(res);
}

void manage::manage_login_submit( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    HttpViewData viewData{};

    viewData.insert("message", std::string("ログイン情報が不正です。"));
    auto response = HttpResponse::newHttpViewResponse("manage_login.csp", viewData);

    std::array<u_char, 64UL> inputHash;
    std::string passHash;
    Json::Value ret;
    bool logined = false;

    {
        std::string pass = req->getParameter("passWord");
        passHash = 
            createDigestArray<char>( pass.c_str(), static_cast<size_t>( pass.length() ), inputHash );
        
    }

    // sql
    std::string sql = "SELECT * from manage.login";
    try{
        auto futureObject = 
            drogon::app()
                .getDbClient("default")
                ->execSqlAsyncFuture(sql);

        if(std::future_status::timeout == futureObject.wait_for(std::chrono::seconds(3))){
            auto res = HttpResponse::newHttpResponse();
            res->setBody("<p>timeout!!</p>");
            res->setStatusCode(k200OK);
            res->setContentTypeCode(CT_TEXT_HTML);
            callback(res);
            return;
        }
        else{
            HttpViewData viewData{};
            auto result = futureObject.get();

            if(0 >= result.size()){
                return;
            }

            std::string storedPassHash = result[0]["pass"].as<std::string>();

            logined = (passHash == storedPassHash);
        }
    }
    catch(const drogon::orm::DrogonDbException &e){
        std::cerr << e.base().what() << '\n';
    }

    if( logined )
    {
        std::string redirect_path;
        auto sessionHolder = req->session();
        sessionHolder->insert("loginState", true);
        if(sessionHolder->find("login_redirect_path"))
        {
            redirect_path = sessionHolder->getOptional<std::string>("login_redirect_path").value_or("/manage");
        }
        else{
            redirect_path = "/manage";
        }
        auto res = HttpResponse::newRedirectionResponse(redirect_path);
        callback(res);
        return;
    }

    callback(response);
}

void manage::manage_changepass( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    bool loginState = false;
    auto sessionHolder = req->getSession();
    if(sessionHolder->find("loginState"))
    {
        loginState = sessionHolder->getOptional<bool>("loginState").value_or(false);
    }
    
    if(loginState){
        HttpViewData viewData{};
        viewData.insert("message", "");
        viewData.insert("succeeded", false);
        auto res = HttpResponse::newHttpViewResponse("manage_changepass.csp", viewData);
        callback(res);
        return;
    }
    else{
        auto res = HttpResponse::newRedirectionResponse("/manage/login");
        req->session()->insert("login_redirect_path", req->getPath());
        callback(res);
    }
}

void manage::manage_changepass_submit( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    std::array<u_char, 64UL> inputHash;
    std::string oldPassHash, newPassHash;
    bool isOkOldPass = false;

    {
        std::string pass = req->getParameter("oldPassWord");
        oldPassHash = 
            createDigestArray<char>( pass.c_str(), static_cast<size_t>( pass.length() ), inputHash );
    }

    // sql
    std::string sql = "SELECT * from manage.login";
    try{
        auto futureObject = 
            drogon::app()
                .getDbClient("default")
                ->execSqlAsyncFuture(sql);

        if(std::future_status::timeout == futureObject.wait_for(std::chrono::seconds(3))){
            auto res = HttpResponse::newHttpResponse();
            res->setBody("<p>timeout!!</p>");
            res->setStatusCode(k200OK);
            res->setContentTypeCode(CT_TEXT_HTML);
            callback(res);
            return;
        }
        else{
            auto result = futureObject.get();

            if(0 >= result.size()){
                return;
            }

            std::string storedPassHash = result[0]["pass"].as<std::string>();

            isOkOldPass = (oldPassHash == storedPassHash);
        }
    }
    catch(const drogon::orm::DrogonDbException &e){
        std::cerr << e.base().what() << '\n';
    }

    // 古いパス合ってる？
    if(!isOkOldPass){
        HttpViewData viewData{};

        viewData.insert("message", std::string("古いパスワードが不正です。"));
        viewData.insert("succeeded", false);
        auto res = HttpResponse::newHttpViewResponse("manage_changepass.csp", viewData);

        callback(res);
        return;
    }

    // 新しいパスは両方が等しい？
    {
        std::string newPass = req->getParameter("newPassWord");
        std::string newPassConfirm = req->getParameter("newPassWordConfirm");
        if(newPass != newPassConfirm){
            HttpViewData viewData{};

            viewData.insert("message", std::string("新しいパスワードが不正です。"));
            viewData.insert("succeeded", false);
            auto res = HttpResponse::newHttpViewResponse("manage_changepass.csp", viewData);

            callback(res);
            return;
        }
        newPassHash = 
            createDigestArray<char>( newPass.c_str(), static_cast<size_t>( newPass.length() ), inputHash );
    }

    // 古いのと新しいの同じじゃない？
    if(oldPassHash == newPassHash){
        HttpViewData viewData{};

        viewData.insert("message", std::string("パスワードが変更されていません。"));
        viewData.insert("succeeded", false);
        auto res = HttpResponse::newHttpViewResponse("manage_changepass.csp", viewData);

        callback(res);
        return;
    }

    // sql
    sql = "UPDATE manage.login SET pass = $1;";
    try{
        auto futureObject = 
            drogon::app()
                .getDbClient("default")
                ->execSqlAsyncFuture(sql, newPassHash);

        if(std::future_status::timeout == futureObject.wait_for(std::chrono::seconds(3))){
            auto res = HttpResponse::newHttpResponse();
            res->setBody("<p>timeout!!</p>");
            res->setStatusCode(k200OK);
            res->setContentTypeCode(CT_TEXT_HTML);
            callback(res);
            return;
        }
        else{
            HttpViewData viewData{};
            viewData.insert("message", "");
            viewData.insert("succeeded", true);
            
            auto res = HttpResponse::newHttpViewResponse("manage_changepass.csp", viewData);
            callback(res);
            return;
        }
    }
    catch(const drogon::orm::DrogonDbException &e){
        std::cerr << e.base().what() << '\n';
    }

    HttpViewData viewData{};
    viewData.insert("message", "謎のエラーが発生しました。");
    viewData.insert("succeeded", false);
    
    auto res = HttpResponse::newHttpViewResponse("manage_changepass.csp", viewData);
    callback(res);
}