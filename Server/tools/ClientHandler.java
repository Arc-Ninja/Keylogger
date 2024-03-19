package Server.tools;

import java.io.*;
import java.net.*;
import java.util.*;
public class ClientHandler extends Thread{
    public static int client =1;
    public static Vector<ClientHandler> handler = new Vector<ClientHandler>(10);
    Socket socket;
    DataInputStream in;
    DataOutputStream out;

    public ClientHandler(Socket socket, int i)throws Exception{
        super(String.valueOf(i));
        this.socket = socket;
        this.socket.setKeepAlive(true);
        socket = null;
        in = new DataInputStream(this.socket.getInputStream());
        out = new DataOutputStream(this.socket.getOutputStream());
    }

    public void run() {
        try {
            String msg = (String) in.readUTF();
            if (msg.equals("exit")) {
                socket.close();
                client--;
                handler.remove(this);
            } else {
                out.writeUTF(socket.getLocalAddress() + ":" + socket.getLocalPort());
                do {
                    System.out.println(socket.getInetAddress() + ":" + socket.getPort() + "->" + msg);
                    msg = (String) in.readUTF();
                } while (!msg.equals("exit"));
                // socket.close();
            }
        } catch (Exception e) {

        } finally {
            System.out.println(getName() + ": completed!");
        }

    }
}
