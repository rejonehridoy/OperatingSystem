import java.util.Scanner;

class WorkProcedure{
    public static int N;
    public static int mutex;
    public static int empty;
    public static int full;
    static int[] buffer;
    static int[] user;
    static int index = 0;


    public WorkProcedure(int n){
        N = n;
        mutex = 1;
        empty = N;
        full = 0;
        buffer = new int[n+1];
        user = new int[n+1];
    }

    public static class Consumer implements Runnable{
        public void run(){
            while (true){
                //wait(full)
                while (full<=0){
                    try {
                        Thread.sleep(1000);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                }
                full--;
                while (mutex<=0){
                    try {
                        Thread.sleep(1000);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                }
                mutex--;

                //consume item
                System.out.println("Consumer: "+user[full]+ ", Consumed Data: "+buffer[full]+ " from the buffer");
                index--;

                //signal(mutex)
                mutex++;
                //signal(empty)
                empty++;
            }
        }
    }

    public static class Producer implements Runnable{
        Scanner sc = new Scanner(System.in);

        public void run(){
            while (true){
                //wait mutex
                while (empty<=0) {
                    try {
                        Thread.sleep(500);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                empty--;
                //wait mutex
                while (mutex<=0){
                    try {
                        Thread.sleep(500);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                mutex--;
                //produced item
                System.out.print("Enter the name of Producer : ");
                int no = sc.nextInt();
                System.out.print("Enter the data : ");
                int data = sc.nextInt();

                buffer[index] = data;
                user[index] = no;
                index++;

                System.out.println("Empty Space: "+(N-index) + " and Full Space:  "+index);

                //signal(mutex);
                mutex++;
                //signal(full);
                full++;
            }
        }
    }
}
public class ProducerConsumer {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the size of buffer : ");
        int n = sc.nextInt();
        WorkProcedure q = new WorkProcedure(n);

        WorkProcedure.Producer producer = new WorkProcedure.Producer();
        WorkProcedure.Consumer consumer = new WorkProcedure.Consumer();

        Thread t1 = new Thread(producer);
        t1.start();
        Thread t2 = new Thread(consumer);
        t2.start();


    }
}
