package Server.tools;

import java.net.*;
import java.io.*;
import java.util.*;
import java.util.concurrent.*;
public class Server {
    public ServerSocket socket;
    public Server(int port)throws Exception {
        this.socket = new ServerSocket(port);
    }
    public Server(InetAddress address,int port)throws Exception {
        this.socket = new ServerSocket(port,1,address);
    }
    public void start()throws Exception {
        Vector<Thread> threads = new Vector<Thread>(10);
    }
}
