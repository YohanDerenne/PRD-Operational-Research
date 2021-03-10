#include "pch.h"
#include "CppUnitTest.h"
#include "../PRD/Instance.h"
#include "../PRD/Instance.cpp"
#include <string>
#include "../PRD/Result.h"
#include "../PRD/Result.cpp"
#include "../PRD/SolverControler.h"
#include "../PRD/SolverControler.cpp"
#include "../PRD/Solver.h"
#include "../PRD/Solver.cpp"
#include "../PRD/Solution.h"
#include "../PRD/Solution.cpp"
#include "../PRD/SolutionPSO.h"
#include "../PRD/SolutionPSO.cpp"
#include "../PRD/PSO.h"
#include "../PRD/PSO.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestPRD
{
	/// <summary>
	/// Tests de la classe Instance
	/// </summary>
	TEST_CLASS(UnitTestInstance)
	{
	public:
		
		/// <summary>
		/// Test si le parseur fonctionne bien
		/// </summary>
		TEST_METHOD(TestParseur)
		{
			Instance instance = Instance();
			try
			{
				bool result = instance.Parse("../UnitTestPRD/instanceTest/I_n6_id2.txt");
				Assert::AreEqual(true, result,L"Aucun problème n'est attendu");
				
				// Premiers parametres
				Assert::AreEqual(6, instance.n);
				Assert::AreEqual(5, instance.m);				
				Assert::AreEqual(4000, instance.c_V);
				Assert::AreEqual(2, instance.id);			

				vector<pair<int, int>> coord;

				// Coordonnées producteur
				coord.push_back({ 122,281 });

				// Coordonnées livreur
				coord.push_back({ 119,88 });

				// Commande 0
				int numCmd = 0;
				Assert::AreEqual(51.0, instance.p[0][numCmd]);
				Assert::AreEqual(24.0, instance.p[1][numCmd]);
				Assert::AreEqual(85.0, instance.p[2][numCmd]);
				Assert::AreEqual(45.0, instance.p[3][numCmd]);
				Assert::AreEqual(17.0, instance.p[4][numCmd]);
				Assert::AreEqual(0, instance.h_WIP[0][numCmd]);
				Assert::AreEqual(2, instance.h_WIP[1][numCmd]);
				Assert::AreEqual(4, instance.h_WIP[2][numCmd]);
				Assert::AreEqual(6, instance.h_WIP[3][numCmd]);
				Assert::AreEqual(7, instance.h_WIP[4][numCmd]);
				Assert::AreEqual(9, instance.h_FIN[numCmd]);
				Assert::AreEqual(71, instance.d[numCmd]);
				Assert::AreEqual(9, instance.p_M[numCmd]);
				coord.push_back({ 149,154 });

				// Commande 1
				numCmd = 1;
				Assert::AreEqual(1.0, instance.p[0][numCmd]);
				Assert::AreEqual(99.0, instance.p[1][numCmd]);
				Assert::AreEqual(35.0, instance.p[2][numCmd]);
				Assert::AreEqual(64.0, instance.p[3][numCmd]);
				Assert::AreEqual(7.0, instance.p[4][numCmd]);
				Assert::AreEqual(0, instance.h_WIP[0][numCmd]);
				Assert::AreEqual(1, instance.h_WIP[1][numCmd]);
				Assert::AreEqual(2, instance.h_WIP[2][numCmd]);
				Assert::AreEqual(4, instance.h_WIP[3][numCmd]);
				Assert::AreEqual(5, instance.h_WIP[4][numCmd]);
				Assert::AreEqual(6, instance.h_FIN[numCmd]);
				Assert::AreEqual(91, instance.d[numCmd]);
				Assert::AreEqual(9, instance.p_M[numCmd]);
				coord.push_back({ 128,129 });

				// Commande 2
				numCmd = 2;
				Assert::AreEqual(53.0, instance.p[0][numCmd]);
				Assert::AreEqual(94.0, instance.p[1][numCmd]);
				Assert::AreEqual(8.0, instance.p[2][numCmd]);
				Assert::AreEqual(79.0, instance.p[3][numCmd]);
				Assert::AreEqual(78.0, instance.p[4][numCmd]);
				Assert::AreEqual(0, instance.h_WIP[0][numCmd]);
				Assert::AreEqual(1, instance.h_WIP[1][numCmd]);
				Assert::AreEqual(3, instance.h_WIP[2][numCmd]);
				Assert::AreEqual(4, instance.h_WIP[3][numCmd]);
				Assert::AreEqual(6, instance.h_WIP[4][numCmd]);
				Assert::AreEqual(7, instance.h_FIN[numCmd]);
				Assert::AreEqual(123, instance.d[numCmd]);
				Assert::AreEqual(10, instance.p_M[numCmd]);
				coord.push_back({ 153,283 });

				// Commande 3
				numCmd = 3;
				Assert::AreEqual(13.0, instance.p[0][numCmd]);
				Assert::AreEqual(8.0, instance.p[1][numCmd]);
				Assert::AreEqual(84.0, instance.p[2][numCmd]);
				Assert::AreEqual(76.0, instance.p[3][numCmd]);
				Assert::AreEqual(52.0, instance.p[4][numCmd]);
				Assert::AreEqual(0, instance.h_WIP[0][numCmd]);
				Assert::AreEqual(1, instance.h_WIP[1][numCmd]);
				Assert::AreEqual(2, instance.h_WIP[2][numCmd]);
				Assert::AreEqual(3, instance.h_WIP[3][numCmd]);
				Assert::AreEqual(5, instance.h_WIP[4][numCmd]);
				Assert::AreEqual(6, instance.h_FIN[numCmd]);
				Assert::AreEqual(441, instance.d[numCmd]);
				Assert::AreEqual(9, instance.p_M[numCmd]);
				coord.push_back({ 103,234 });

				// Commande 4
				numCmd = 4;
				Assert::AreEqual(86.0, instance.p[0][numCmd]);
				Assert::AreEqual(54.0, instance.p[1][numCmd]);
				Assert::AreEqual(67.0, instance.p[2][numCmd]);
				Assert::AreEqual(21.0, instance.p[3][numCmd]);
				Assert::AreEqual(27.0, instance.p[4][numCmd]);
				Assert::AreEqual(0, instance.h_WIP[0][numCmd]);
				Assert::AreEqual(2, instance.h_WIP[1][numCmd]);
				Assert::AreEqual(3, instance.h_WIP[2][numCmd]);
				Assert::AreEqual(5, instance.h_WIP[3][numCmd]);
				Assert::AreEqual(6, instance.h_WIP[4][numCmd]);
				Assert::AreEqual(8, instance.h_FIN[numCmd]);
				Assert::AreEqual(449, instance.d[numCmd]);
				Assert::AreEqual(7, instance.p_M[numCmd]);
				coord.push_back({ 239,138 });

				// Commande 5
				numCmd = 5;
				Assert::AreEqual(47.0, instance.p[0][numCmd]);
				Assert::AreEqual(25.0, instance.p[1][numCmd]);
				Assert::AreEqual(4.0, instance.p[2][numCmd]);
				Assert::AreEqual(66.0, instance.p[3][numCmd]);
				Assert::AreEqual(20.0, instance.p[4][numCmd]);
				Assert::AreEqual(0, instance.h_WIP[0][numCmd]);
				Assert::AreEqual(1, instance.h_WIP[1][numCmd]);
				Assert::AreEqual(3, instance.h_WIP[2][numCmd]);
				Assert::AreEqual(5, instance.h_WIP[3][numCmd]);
				Assert::AreEqual(6, instance.h_WIP[4][numCmd]);
				Assert::AreEqual(7, instance.h_FIN[numCmd]);
				Assert::AreEqual(536, instance.d[numCmd]);
				Assert::AreEqual(5, instance.p_M[numCmd]);
				coord.push_back({ 215,228 });

				// Distances
				vector<vector<int>> t;
				for (size_t i = 0; i < coord.size() ; i++) {
					vector<int> row;
					for (size_t j = 0; j < coord.size(); j++) {
						row.push_back(sqrt(pow(coord[i].first - coord[j].first, 2) + pow(coord[i].second - coord[j].second, 2)));
					}
					t.push_back(row);					
				}
				// Check
				for (int i = 0; i < instance.n + 1; i++) {
					for (int j = 0; j < instance.n + 1; j++) {
						Assert::AreEqual(t[i][j], instance.t[i][j]);
					}
				}				
			}
			catch (const std::exception& exc)
			{
				Assert::Fail(L"Exception non attendue");
			}
		}

		/// <summary>
		/// Test du parseur avec un chemin invalide
		/// </summary>
		TEST_METHOD(TestInvalidPathParse)
		{
			Instance instance = Instance();
			try
			{
				bool result = instance.Parse("../UnitTestPRD/instanceTest/unknow.txt");
				Assert::Fail(L"Une exception d'argument invalide est attendu");
			}
			catch (const std::invalid_argument& ia) {
				
			}
			catch (const std::exception&)
			{
				Assert::Fail(L"Une exception d'argument invalide est attendu");
			}
		}

		/// <summary>
		/// Test si le parseur releve bien une exception sur des fichiers ou le format n'est pas bon
		/// </summary>
		TEST_METHOD(TestBadInstanceParse)
		{
			Instance instance = Instance();
			try
			{
				bool result = instance.Parse("../UnitTestPRD/badInstanceTest/I_n6_id2.txt");
				Assert::Fail(L"Une exception est attendu");
			}
			catch (const std::invalid_argument& ia) {
				Assert::Fail(L"Une autre exception est attendu");
			}
			catch (const std::exception& exc)
			{
				cerr << exc.what();
			}

			try
			{
				bool result = instance.Parse("../UnitTestPRD/badInstanceTest/I_n8_id4.txt");
				Assert::Fail(L"Une exception est attendu");
			}
			catch (const std::invalid_argument& ia) {
				Assert::Fail(L"Une autre exception est attendu");
			}
			catch (const std::exception& exc)
			{
				cerr << exc.what();
			}

		}

		/// <summary>
		/// Test le constructeur de copie de la classe Instance
		/// </summary>
		TEST_METHOD(TestCopyInstance)
		{
			Instance* inst1 = new Instance();
			try
			{
				bool result = inst1->Parse("../UnitTestPRD/instanceTest/I_n6_id2.txt");
				Instance* inst2 = new Instance(*inst1);
				Assert::AreEqual(51.0, inst2->p[0][0]);
				delete inst1;
				Assert::AreEqual(1.0, inst2->p[0][1]);
				delete inst2;
			}
			catch (exception exc) {
				//cerr << exc.what();
			}
		}
	};

	/// <summary>
	/// Test les elements de la classe Result
	/// </summary>
	TEST_CLASS(UnitTestResult)
	{
	public:
		/// <summary>
		/// Test le constructeur de copie de la classe Result
		/// </summary>
		TEST_METHOD(TestCopyResult)
		{
			Instance* instance = new Instance();
			try
			{
				bool result = instance->Parse("../UnitTestPRD/instanceTest/I_n6_id2.txt");
				Result* res1 = new Result(*instance);
				Result* res2 = new Result(*res1);
				//Assert::AreNotEqual(res1, res2);
				Assert::AreEqual(51.0, res2->inst.p[0][0]);
				Assert::AreEqual(res1->IC_WIP, res2->IC_WIP);
				delete res1;
				Assert::AreEqual(1.0, res2->inst.p[0][1]);
				delete res2;
			}
			catch (exception exc) {
				//cerr << exc.what();
			}
			delete instance;
		}
	};

	/// <summary>
	/// Test les elements de la classe SolverControler
	/// </summary>
	TEST_CLASS(UnitTestSolverControler)
	{
	public:
		TEST_METHOD(TestImportDirectory)
		{
			SolverControler control = SolverControler();
			Assert::AreEqual(true,control.ImportInstances("../UnitTestPRD/instanceTest"));
			list<Instance> list = control.getInstances();
			auto it = list.begin();
			std::advance(it, 0);
			Instance inst = *it;
			size_t expected_size = 2;
			Assert::AreEqual(expected_size, control.getInstances().size());
			Assert::AreEqual(51.0, inst.p[0][0]);
			std::advance(it, 1);
			inst = *it;
			Assert::AreEqual(47.0, inst.p[0][0]);
		}

		TEST_METHOD(TestExportResults)
		{
			remove("../UnitTestPRD/resultTest/resultat.txt");
			// Init
			SolverControler control = SolverControler();
			control.ImportInstances("../UnitTestPRD/instanceTest");

			list<Instance> list = control.getInstances();
			auto it = list.begin();
			std::advance(it, 0);
			Instance inst = *it;
			Result res1 = Result(inst);
			std::advance(it, 1);
			inst = *it;
			Result res2 = Result(inst);

			res1.IC_FIN = 123;
			res1.PPC_M = 456;
			res1.cout_total = 626;
			res1.IC_WIP = 47;

			res2.IC_FIN = 78;
			res2.PPC_M = 98;
			res2.cout_total = 231;
			res2.IC_WIP = 55;

			control.AddResult(res1);
			control.AddResult(res2);

			// Export
			Assert::AreEqual(true,control.ExportResults("../UnitTestPRD/resultTest/resultat.txt"));

			// Check
			ifstream file;
			file.open("../UnitTestPRD/resultTest/resultat.txt");
			if (!file) {
				Assert::Fail(L"Ne retrouve le fichier résultat");
			}

			int id;
			int n;
			double ct;
			double cwip;
			double cfin;
			double cr;

			file >> id;
			file >> n;
			file >> ct;
			file >> cwip;
			file >> cfin;
			file >> cr;
			Assert::AreEqual(2,id);
			Assert::AreEqual(6, n);
			Assert::AreEqual(626.0, ct);
			Assert::AreEqual(47.0, cwip);
			Assert::AreEqual(123.0, cfin);
			Assert::AreEqual(456.0, cr);

			file >> id;
			file >> n;
			file >> ct;
			file >> cwip;
			file >> cfin;
			file >> cr;
			Assert::AreEqual(4, id);
			Assert::AreEqual(8, n);
			Assert::AreEqual(231.0, ct);
			Assert::AreEqual(55.0, cwip);
			Assert::AreEqual(78.0, cfin);
			Assert::AreEqual(98.0, cr);

			file.close();
		}

		TEST_METHOD(TestExportResultsBadPath)
		{
			SolverControler control = SolverControler();
			Instance inst =  Instance();
			Result res1 =  Result(inst);
			control.AddResult(res1);
			Assert::AreEqual(false, control.ExportResults("../UnitTestPRD/resultTest/resultat.data"));
			Assert::AreEqual(false, control.ExportResults("../UnitTestPRD/resultTest/resultat"));
			Assert::AreEqual(false, control.ExportResults("../UnitTestPRD/resultTest/"));
			Assert::AreEqual(true, control.ExportResults("../UnitTestPRD/resultTest/resTmp.txt"));
			Assert::AreEqual(false, control.ExportResults("../UnitTestPRD/resultTest/resTmp.txt"));
			remove("../UnitTestPRD/resultTest/resTmp.txt");
		}

		TEST_METHOD(TestImportDirWithBadFormat)
		{
			SolverControler control = SolverControler();
			Assert::AreEqual(false, control.ImportInstances("../UnitTestPRD/BadInstanceTest"));
		}
	};

	TEST_CLASS(UnitTestSolution)
	{
	public:
		TEST_METHOD(TestDecode)
		{
			// === INSTANCE

			Instance inst = Instance();
			inst.m = 3;
			inst.n = 5;			
			inst.p = vector<vector<double>>(inst.m, vector<double>(inst.n, 1));
			inst.d = vector<int>(inst.n, 13);
			inst.h_WIP = vector<vector<int>>(inst.m, vector<int>(inst.n, 1));
			inst.t = vector<vector<int>>(inst.n+2, vector<int>(inst.n+2, 1));
			inst.p_M = vector<int>(inst.n, 3);
			inst.h_FIN = vector<int>(inst.n, 2);
			inst.c_V = 5;

			// === SOLUTION

			Solution sol = Solution(inst);

			sol.sv1.push_back(-0.8);
			sol.sv1.push_back(3.7);
			sol.sv1.push_back(-1.5);
			sol.sv1.push_back(2.3);
			sol.sv1.push_back(1.1);

			sol.sv2.push_back(0.2);
			sol.sv2.push_back(1.8);
			sol.sv2.push_back(2.7);
			sol.sv2.push_back(0.6);
			sol.sv2.push_back(1.2);

			sol.sv3 = vector<vector<double>>(inst.m, vector<double>(inst.n, 1));

			// === RESULT

			Result res = sol.Decode();

			Assert::AreEqual(2, sol.ordre[0]);
			Assert::AreEqual(0, sol.ordre[1]);
			Assert::AreEqual(4, sol.ordre[2]);
			Assert::AreEqual(3, sol.ordre[3]);
			Assert::AreEqual(1, sol.ordre[4]);

			Assert::AreEqual(0, sol.affectV[0]);
			Assert::AreEqual(2, sol.affectV[1]);
			Assert::AreEqual(3, sol.affectV[2]);
			Assert::AreEqual(1, sol.affectV[3]);
			Assert::AreEqual(1, sol.affectV[4]);

			Assert::AreEqual(10.0, res.C[0][1]);
			Assert::AreEqual(14.0, res.C[2][1]);
			Assert::AreEqual(10.0, res.IC_WIP);
			Assert::AreEqual(4.0, res.IC_FIN);

			Assert::AreEqual(8.0, res.F[0]);
			Assert::AreEqual(12.0, res.F[1]);
			Assert::AreEqual(14.0, res.F[2]);
			Assert::AreEqual(6.0, res.F[3]);

			Assert::AreEqual(14.0, res.IC);
			Assert::AreEqual(9.0, res.PPC_M);
			Assert::AreEqual(20, res.VC);
			Assert::AreEqual(43.0, res.cout_total); 

		}

		TEST_METHOD(TestDecode2)
		{
			// === INSTANCE

			Instance inst = Instance();
			inst.m = 3;
			inst.n = 5;
			inst.p = vector<vector<double>>(inst.m, vector<double>(inst.n, 1));
			inst.d = vector<int>(inst.n, 13);
			inst.h_WIP = vector<vector<int>>(inst.m, vector<int>(inst.n, 1));
			inst.t = vector<vector<int>>(inst.n+2, vector<int>(inst.n+2, 1));
			inst.p_M = vector<int>(inst.n, 1);
			inst.h_FIN = vector<int>(inst.n, 2);
			inst.c_V = 5;

			// modif
			inst.h_WIP[1][0] = 2;
			inst.p[1][2] = 3;
			inst.d[0] = 7;
			inst.t[3 + 2][4 + 2] = 3;
			inst.t[4 + 2][3 + 2] = 3;
			inst.t[0][0 + 2] = 2;
			inst.t[0 + 2][0] = 2;
			inst.p_M[1] = 4;
			inst.h_FIN[4] = 1;

			// === SOLUTION

			Solution sol = Solution(inst);

			sol.sv1.push_back(-0.8);
			sol.sv1.push_back(3.7);
			sol.sv1.push_back(-1.5);
			sol.sv1.push_back(2.3);
			sol.sv1.push_back(1.1);

			sol.sv2.push_back(0.2);
			sol.sv2.push_back(1.8);
			sol.sv2.push_back(2.7);
			sol.sv2.push_back(0.6);
			sol.sv2.push_back(1.2);

			sol.sv3 = vector<vector<double>>(inst.m, vector<double>(inst.n, 0));

			// Modif
			sol.sv3[0][2] = 1;
			sol.sv3[1][2] = 2;
			sol.sv3[2][2] = 1;
			sol.sv3[1][0] = 1;
			

			// === RESULT

			Result res = sol.Decode();

			Assert::AreEqual(2, sol.ordre[0]);
			Assert::AreEqual(0, sol.ordre[1]);
			Assert::AreEqual(4, sol.ordre[2]);
			Assert::AreEqual(3, sol.ordre[3]);
			Assert::AreEqual(1, sol.ordre[4]);

			Assert::AreEqual(10.0, res.F[0]);
			Assert::AreEqual(12.0, res.F[1]);
			Assert::AreEqual(13.0, res.F[2]);
			Assert::AreEqual(9.0, res.F[3]);
			Assert::AreEqual(-1.0, res.F[4]);

			Assert::AreEqual(28.0, res.IC_WIP);
			Assert::AreEqual(1.0, res.IC_FIN);
			Assert::AreEqual(29.0, res.IC);

			Assert::AreEqual(12.0, res.PPC_M);
			
			Assert::AreEqual(20, res.VC);
			Assert::AreEqual(29.0+12.0+20.0, res.cout_total);
		}

	};

	TEST_CLASS(UnitTestPSO) {
	public:
		TEST_METHOD(TestPSO) {
			Instance inst = Instance("../UnitTestPRD/I_n5_id0.txt");
			PSO solver = PSO(inst, 50, 17);
			Result res = solver.Solve();

			string log = "Durée résolution : " + std::to_string(res.dureeSec);
			log += "\nDernieres particules : " + std::to_string(solver.particules[2].resultatDecode.cout_total);
			log += "\nBest particule : " + std::to_string(res.cout_total);
			Logger::WriteMessage(log.c_str());

			Assert::AreEqual(true, res.VerificationContraintes());
			Assert::AreEqual(true, res.cout_total < solver.GetReference().cout_total);
		}

		TEST_METHOD(TestReference) {
			Instance inst = Instance("../UnitTestPRD/I_n5_id0.txt");
			PSO solver = PSO(inst, 200, 17);
			Result ref = solver.GetReference();

			string log = "Cout total ref : " + std::to_string(ref.cout_total);
			Logger::WriteMessage(log.c_str());

			Assert::AreEqual(true, ref.VerificationContraintes());
		}
	};
}
