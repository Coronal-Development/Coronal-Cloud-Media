import tornado.ioloop
import tornado.web


class GetLoginPage(tornado.web.RequestHandler):
    def get(self, *args, **kwargs):
        self.render('html/login.html');

class Login(tornado.web.RequestHandler):
    def post(self, *args, **kwargs):
        username = self.get_argument("username");
        password = self.get_argument("password");
        self.write(username+","+password);

if __name__ == "__main__":
    app = tornado.web.Application(handlers=[
        (r'/', GetLoginPage),
        (r'/Login', Login)
    ]);
    app.listen(8888);
    tornado.ioloop.IOLoop.instance().start();