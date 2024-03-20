package Client;
import java.io.*;
import java.net.Socket;


public class app{

    
    public static void main(String[] args) throws Exception{
        Socket s = null;
        try{
            s = new Socket("localhost",80);
            System.out.println("Connected to Server!");
            System.out.println(s.getLocalAddress() + ":" + s.getLocalPort() + ":" + s.getPort());
        }
        catch(Exception e){
            System.out.println(e);
        }



        try{
        String str = "test string";
        byte[] data = str.getBytes();
        DataOutputStream dos = new DataOutputStream(s.getOutputStream());
        dos.write(data);
        System.out.println("data written!");
        s.close();
        }
        catch(Exception e){
            System.out.println(e);
        }
        


    }
}

