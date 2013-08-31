/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javafeeder;

import java.net.Socket;

/**
 *
 * @author dannyt
 */
public class Application {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        try
        {
            Socket  sock = new Socket("127.0.0.1", 8501);
            sock.setSendBufferSize(4096);
            
            System.out.println("socket connection successful");
            
            String s = new String("JavaTest/hello world\0");

            sock.getOutputStream().write(s.getBytes());
            
            sock.getOutputStream().write( new String("JavaTest,threadid/another test\0").getBytes() );
            
//            Trace t = new Trace("TestApp", "hello world");
//            t.Send(sock);
            
            Thread.sleep(5000);
            
            System.out.println("closing socket connection");
        }
        catch ( Exception e )
        {
            System.err.println("socket connection failed");
        }
        
    }
}
