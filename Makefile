correctness_compile:
	g++-12 -O2 seq_bfs.cpp par_bfs.cpp test_correctness.cpp -o correctness.out

correctness_run:
	PARLAY_NUM_THREADS=4 ./correctness.out

time_compile:
	g++-12 -O2 seq_bfs.cpp par_bfs.cpp test_time.cpp -o time.out

time_run:
	PARLAY_NUM_THREADS=4 ./time.out