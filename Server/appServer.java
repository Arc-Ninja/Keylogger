
import java.io.*;
import java.net.*;

public class appServer{
    public static void main(String[] args) throws Exception{
        ServerSocket serverSocket = new ServerSocket(6666);
        Socket socket = serverSocket.accept();
        DataInputStream in = new DataInputStream(socket.getInputStream());
        // DataOutputStream out = new DataOutputStream(this.socket.getOutputStream());
        System.out.println("connected");
        while (true) {
            String msg = (String) in.readUTF();
        System.out.println(msg);
        }
        
    }
}