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
    
    public Trace( String module, String text ) {
        
        m_DataSize = Integer.SIZE/8 + Integer.SIZE/8 + text.length();
        m_Text = text;
        m_Module = module;
    }   
    
    
    public void Send(Socket sock) {
        
        try
        {
            ByteBuffer      buff = ByteBuffer.allocate(4096);
            
            int dataSize =  Integer.SIZE/8 + 
                    
                            Integer.SIZE/8 +
                            Integer.SIZE/8 +
                    
                            Integer.SIZE/8 +
                            m_Module.length() +
                    
                            Integer.SIZE/8 + 
                            m_Text.length();
            
//            buff.putInt(Integer.reverseBytes(0xFFFE));
            buff.putInt(0xFFFE);
            buff.putInt(dataSize);
            buff.putInt(m_DataType);
            
            buff.putInt(4);
            buff.putInt(2);
            
            buff.putInt(m_Module.length());
            buff.put(m_Module.getBytes());
            
            buff.putInt(m_Text.length());
            buff.put(m_Text.getBytes());
            
//            buff.putInt(Integer.reverseBytes(m_DataSize));
//            buff.putInt(Integer.reverseBytes(m_DataType));
//            buff.putInt(Integer.reverseBytes(m_Text.length()));

            

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
    String      m_Module;
}
