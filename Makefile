all:
	g++ -std=c++17 main.cpp solve/solve.cpp -o solve_app
	g++ -std=c++17 testsolve.cpp solve/solve.cpp -lcppunit -o testsolve_app

test:
	chmod +x solve_app
	./testsolve_app

clean:
	$(RM) solve_app testsolve_app
