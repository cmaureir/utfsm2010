import java.io.*;
import java.lang.Thread;

public class Cerdito {
	public static void main(String args[]) throws Exception{
	         BufferedReader frase = new BufferedReader(new FileReader(args[0]));
	         String linea;
	         String tipoCarne;
	         int[] tiempoLlegada = new int[100];
	         int[] tiempoDemora = new int[100];
	         int i=0,vendedoresDisponibles=5;
			
		 Cliente cliente = new Cliente();
		 cliente.habla();
	         linea = frase.readLine();
	         while(linea != null){
	                 String[] partes = linea.split("\\s");
	                 tiempoLlegada[i] = Integer.parseInt(partes[0]);
	                 tiempoDemora[i] = Integer.parseInt(partes[1]);
	                 tipoCarne = partes[2];
	                 System.out.println(tiempoLlegada[i]+" "+tiempoDemora[i]+" "+tipoCarne);
	                 linea = frase.readLine();
	                 i++;
	         }
		

	         System.out.println("fin programa!");
	}
}
