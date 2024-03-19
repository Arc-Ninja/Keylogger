package Server.tools;

import java.net.*;
public class Server {
    public ServerSocket serverSocket;
    public Server(int port)throws Exception {
        this.serverSocket = new ServerSocket(port);
    }
    public Server(InetAddress address,int port)throws Exception {
        this.serverSocket = new ServerSocket(port,1,address);
    }
    public void start()throws Exception {

        while (true) {
            
            if ( ClientHandler.client<= 10) {
                Socket socket = serverSocket.accept();
                ClientHandler.handler.add(new ClientHandler(socket, ClientHandler.handler.size()+100 + ClientHandler.client));
                ClientHandler.handler.get(ClientHandler.client).start();
                socket = null;
                ClientHandler.client++;
            }
        }
    }
}
