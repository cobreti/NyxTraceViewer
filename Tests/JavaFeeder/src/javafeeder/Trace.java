/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javafeeder;

import java.math.BigInteger;
import java.net.Socket;
import java.nio.ByteBuffer;

/**
 *
 * @author dannyt
 */
public class Trace {
    
    public Trace( String text ) {
        
        m_DataSize = Integer.SIZE/8 + Integer.SIZE/8 + text.length();
        m_Text = text;
    }   
    
    
    public void Send(Socket sock) {
        
        try
        {
            ByteBuffer      buff = ByteBuffer.allocate(4096);
            
            buff.putInt(Integer.reverseBytes(m_DataSize));
            buff.putInt(Integer.reverseBytes(m_DataType));
            buff.putInt(Integer.reverseBytes(m_Text.length()));
            buff.put(m_Text.getBytes());
            

            for (int pos = 0; pos < buff.position(); ++pos)
            {
                sock.getOutputStream().write(buff.get(pos));
            }
            
//            sock.getOutputStream().write(m_DataSize);
//            sock.getOutputStream().write(m_DataType);
//            sock.getOutputStream().write(m_Text.length());
//            sock.getOutputStream().write(m_Text.getBytes());
        }
        catch ( Exception ex )
        {
            
        }
    }
    
    
    int         m_DataSize = 0;
    int         m_DataType = 3;
    String      m_Text;
}
