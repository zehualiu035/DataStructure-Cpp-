package nachos.threads;

import nachos.machine.*;

/**
 * A <i>communicator</i> allows threads to synchronously exchange 32-bit
 * messages. Multiple threads can be waiting to <i>speak</i>, and multiple
 * threads can be waiting to <i>listen</i>. But there should never be a time
 * when both a speaker and a listener are waiting, because the two threads can
 * be paired off at this point.
 */
public class Communicator {
	/**
	 * Allocate a new communicator.
	 */
	
	private static int word  = 111;
	public Communicator() {
	}

	/**
	 * Wait for a thread to listen through this communicator, and then transfer
	 * <i>word</i> to the listener.
	 * 
	 * <p>
	 * Does not return until this thread is paired up with a listening thread.
	 * Exactly one listener should receive <i>word</i>.
	 * 
	 * @param word the integer to transfer.
	 */
	public void speak(int word) {
		this.word=word;
	}

	/**
	 * Wait for a thread to speak through this communicator, and then return the
	 * <i>word</i> that thread passed to <tt>speak()</tt>.
	 * 
	 * @return the integer transferred.
	 */
	public int listen() {
		return word;
	}
	
	public static void commTest5() {
		final Communicator com = new Communicator();
		final Communicator anotherCom = new Communicator();
		final long times[] = new long[4];
		final int words[] = new int[2];
		final int anotherWords[] = new int[2];
		
		
		KThread speaker1 = new KThread( new Runnable () {
			public void run() {
			    com.speak(1);
			    times[0] = Machine.timer().getTime();
			}
		    });
		speaker1.setName("S1");
		KThread.currentThread().yield();
		KThread listener1 = new KThread( new Runnable () {
			public void run() {
			    times[2] = Machine.timer().getTime();
			    words[0] = com.listen();
			}
		    });
		listener1.setName("L1");
		
		speaker1.fork();listener1.fork();speaker1.join(); listener1.join();
		for(int i=1;i<=4;i++)
			KThread.currentThread().yield();
		
		KThread speaker2 = new KThread( new Runnable () {
			public void run() {
				com.speak(9);
			    times[1] = Machine.timer().getTime();
			}
		    });
		speaker2.setName("S2");
		KThread listener2 = new KThread( new Runnable () {
			public void run() {
			    times[3] = Machine.timer().getTime();
			    words[1] = com.listen();
			}
		    });
		listener2.setName("L2");
		
		speaker2.fork(); listener2.fork();speaker2.join();  listener2.join();
		for(int i=1;i<=4;i++)
		KThread.currentThread().yield();
		
		//开始执行另外一个Communicator的speak()和listen()函数，以验证两个Communicator不会互相干扰
		KThread speaker3 = new KThread( new Runnable () {
			public void run() {
				anotherCom.speak(4);
			    times[0] = Machine.timer().getTime();
			}
		    });
		speaker3.setName("S3");
		KThread listener3 = new KThread( new Runnable () {
			public void run() {
			    times[0] = Machine.timer().getTime();
			    anotherWords[0] = anotherCom.listen();
			}
		    });
		listener3.setName("L3");
		
		speaker3.fork(); listener3.fork();speaker3.join();  listener3.join();
		for(int i=1;i<=4;i++)
		KThread.currentThread().yield();
		
		KThread speaker4 = new KThread( new Runnable () {
			public void run() {
				anotherCom.speak(5);
			    times[1] = Machine.timer().getTime();
			}
		    });
		speaker4.setName("S4");
		KThread listener4 = new KThread( new Runnable () {
			public void run() {
			    times[1] = Machine.timer().getTime();
			    anotherWords[1] = anotherCom.listen();
			}
		    });
		listener4.setName("L4");
		
		speaker4.fork(); listener4.fork();speaker4.join();  listener4.join();
		for(int i=1;i<=4;i++)
		KThread.currentThread().yield();
		
		System.out.println("word[0]:"+words[0]+";word[1]:"+words[1]);
		System.out.println("anotherword[0]:"+anotherWords[0]+";anotherword[1]:"+anotherWords[1]);
		
	}
    public static void commTest6() {
	final Communicator com = new Communicator();
	final long times[] = new long[4];
	final int words[] = new int[2];
	KThread speaker1 = new KThread( new Runnable () {
		public void run() {
		    com.speak(1);
		    times[0] = Machine.timer().getTime();
		}
	    });
	speaker1.setName("S1");
	KThread speaker2 = new KThread( new Runnable () {
		public void run() {
		    com.speak(9);
		    times[1] = Machine.timer().getTime();
		}
	    });
	speaker2.setName("S2");
	KThread listener1 = new KThread( new Runnable () {
		public void run() {
		    times[2] = Machine.timer().getTime();
		  //  words[0] = com.listen();
		}
	    });
	listener1.setName("L1");
	KThread listener2 = new KThread( new Runnable () {
		public void run() {
		    times[3] = Machine.timer().getTime();
		  //  words[1] = com.listen();
		}
	    });
	listener2.setName("L2");
    
	speaker1.fork(); speaker2.fork(); listener1.fork(); listener2.fork();
	speaker1.join(); speaker2.join(); listener1.join(); listener2.join();
    
	Lib.assertTrue(words[0] == 1, "Didn't listen back spoken word."); 
	Lib.assertTrue(words[1] == 9, "Didn't listen back spoken word.");
	Lib.assertTrue(times[0] > times[2], "speak() returned before listen() called.");
	Lib.assertTrue(times[1] > times[3], "speak() returned before listen() called.");
	System.out.println("commTest6 successful!");
    }

    // Invoke Communicator.selfTest() from ThreadedKernel.selfTest()

    public static void selfTest() {
    commTest5();
    }
}
