// Java program to implement Round Robin 
// Scheduling with different arrival time 
class roundrobin { 
	public static void roundRobin(String pr[], int a1[], int b[], int n) 
	{ 
		// result of average times 
		int res1 = 0; 
		int resc1 = 0; 

		// for sequence storage 
		String seq = new String(); 

		// copy the burst array and arrival array for not effecting the actual array 
		int r2[] = new int[b.length]; 
		int r1[] = new int[a1.length]; 

		for (int i = 0; i < r2.length; i++) 
		{ 
			r2[i] = b[i]; 
			r1[i] = a1[i]; 
		} 

		// critical time of system 
		int z = 0; 

		// for store the waiting time 
		int w[] = new int[pr.length]; 

		// for store the Completion time 
		int comp[] = new int[pr.length]; 

		while (true)
		 { 
			boolean flag = true; 
			for (int i = 0; i < pr.length; i++) 
			{ 

				// these condition for if 
				// arrival is not on zero 

				// check that if there come before qtime 
				if (r1[i] <= z)
				 { 
					if (r1[i] <= n)
					 { 
						if (r2[i] > 0)
						 { 
							flag = false; 
							if (r2[i] > n)
							 { 

								// make decrease the b time 
								z = z + n; 
								r2[i] = r2[i] - n; 
								r1[i] = r1[i] + n; 
								seq += "->" + pr[i]; 
							} 
							else { 

								// for last time 
								z = z + r2[i]; 

								// store comp time 
								comp[i] = z - a1[i]; 

								// store wait time 
								w[i] = z - b[i] - a1[i]; 
								r2[i] = 0; 

								// add sequence 
								seq += "->" + pr[i]; 
							} 
						} 
					} 
					else if (r1[i] > n)
					 { 

						// is any have less arrival time 
						// the coming process then execute them 
						for (int j = 0; j < pr.length; j++) { 

							// compare 
							if (r1[j] < r1[i])
							 { 
								if (r2[j] > 0)
								 { 
									flag = false; 
									if (r2[j] > n)
									 { 
										z = z + n; 
										r2[j] = r2[j] - n; 
										r1[j] = r1[j] + n; 
										seq += "->" + pr[j]; 
									} 
									else { 
										z = z + r2[j]; 
										comp[j] = z - a1[j]; 
										w[j] = z - b[j] - a1[j]; 
										r2[j] = 0; 
										seq += "->" + pr[j]; 
									} 
								} 
							} 
						} 

						// now the previous porcess according to ith is process 
						if (r2[i] > 0) { 
							flag = false; 

							// Check for greaters 
							if (r2[i] > n) { 
								z = z + n; 
								r2[i] = r2[i] - n; 
								r1[i] = r1[i] + n; 
								seq += "->" + pr[i]; 
							} 
							else { 
								z = z + r2[i]; 
								comp[i] = z - a1[i]; 
								w[i] = z - b[i] - a1[i]; 
								r2[i] = 0; 
								seq += "->" + pr[i]; 
							} 
						} 
					} 
				} 

				// if no process is come on thse critical 
				else if (r1[i] > z) { 
					z++; 
					i--; 
				} 
			} 
			// for exit the while loop 
			if (flag) { 
				break; 
			} 
		} 

		System.out.println("Process Name   Completion Time   Waiting Time"); 
		for (int i = 0; i < pr.length; i++) { 
			System.out.println(" " + pr[i] + "  		 " + comp[i] + " 		  " + w[i]); 

			res1 = res1 + w[i]; 
			resc1 = resc1 + comp[i]; 
		} 

		System.out.println("Average waiting time is "+ (float)res1 / pr.length); 
		System.out.println("Average compilation time is "+ (float)resc1 / pr.length); 
		System.out.println("Sequence is like that " + seq); 
	} 

	// Driver Code 
	public static void main(String args[]) 
	{ 
		// name of the process 
		String name[] = { "p1", "p2", "p3", "p4" }; 

		// arrival for every process 
		int arrivaltime[] = { 0,5,13,26 }; 

		// burst time for every process 
		int bursttime[] = { 20,36,19,42 }; 

		// quantum time of each process 
		int q = 10; 

		// cal the function for output 
		roundRobin(name, arrivaltime, bursttime, q); 
	} 
}
