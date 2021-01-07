#include "pch.h"
#include "CppUnitTest.h"
#include "../PRD/Instance.cpp"
#include <string>
#include "../PRD/Result.cpp"

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
			Instance * instance = new Instance();
			try
			{
				bool result = instance->Parse("../UnitTestPRD/instanceTest/I_n6_id2.txt");
				Assert::AreEqual(true, result,L"Aucun probl�me n'est attendu");
				
				// Premiers parametres
				Assert::AreEqual(6, instance->n);
				Assert::AreEqual(5, instance->m);				
				Assert::AreEqual(4000, instance->c_V);
				Assert::AreEqual(2, instance->id);			

				vector<pair<int, int>> coord;

				// Coordonn�es producteur
				coord.push_back({ 122,281 });

				// Coordonn�es livreur
				coord.push_back({ 119,88 });

				// Commande 0
				int numCmd = 0;
				Assert::AreEqual(51, instance->p[numCmd][0]);
				Assert::AreEqual(24, instance->p[numCmd][1]);
				Assert::AreEqual(85, instance->p[numCmd][2]);
				Assert::AreEqual(45, instance->p[numCmd][3]);
				Assert::AreEqual(17, instance->p[numCmd][4]);
				Assert::AreEqual(0, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(2, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(4, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(6, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(7, instance->h_WIP[numCmd][4]);
				Assert::AreEqual(9, instance->h_FIN[numCmd]);
				Assert::AreEqual(71, instance->d[numCmd]);
				Assert::AreEqual(9, instance->p_M[numCmd]);
				coord.push_back({ 149,154 });

				// Commande 1
				numCmd = 1;
				Assert::AreEqual(1, instance->p[numCmd][0]);
				Assert::AreEqual(99, instance->p[numCmd][1]);
				Assert::AreEqual(35, instance->p[numCmd][2]);
				Assert::AreEqual(64, instance->p[numCmd][3]);
				Assert::AreEqual(7, instance->p[numCmd][4]);
				Assert::AreEqual(0, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(1, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(2, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(4, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(5, instance->h_WIP[numCmd][4]);
				Assert::AreEqual(6, instance->h_FIN[numCmd]);
				Assert::AreEqual(91, instance->d[numCmd]);
				Assert::AreEqual(9, instance->p_M[numCmd]);
				coord.push_back({ 128,129 });

				// Commande 2
				numCmd = 2;
				Assert::AreEqual(53, instance->p[numCmd][0]);
				Assert::AreEqual(94, instance->p[numCmd][1]);
				Assert::AreEqual(8, instance->p[numCmd][2]);
				Assert::AreEqual(79, instance->p[numCmd][3]);
				Assert::AreEqual(78, instance->p[numCmd][4]);
				Assert::AreEqual(0, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(1, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(3, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(4, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(6, instance->h_WIP[numCmd][4]);
				Assert::AreEqual(7, instance->h_FIN[numCmd]);
				Assert::AreEqual(123, instance->d[numCmd]);
				Assert::AreEqual(10, instance->p_M[numCmd]);
				coord.push_back({ 153,283 });

				// Commande 3
				numCmd = 3;
				Assert::AreEqual(13, instance->p[numCmd][0]);
				Assert::AreEqual(8, instance->p[numCmd][1]);
				Assert::AreEqual(84, instance->p[numCmd][2]);
				Assert::AreEqual(76, instance->p[numCmd][3]);
				Assert::AreEqual(52, instance->p[numCmd][4]);
				Assert::AreEqual(0, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(1, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(2, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(3, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(5, instance->h_WIP[numCmd][4]);
				Assert::AreEqual(6, instance->h_FIN[numCmd]);
				Assert::AreEqual(441, instance->d[numCmd]);
				Assert::AreEqual(9, instance->p_M[numCmd]);
				coord.push_back({ 103,234 });

				// Commande 4
				numCmd = 4;
				Assert::AreEqual(86, instance->p[numCmd][0]);
				Assert::AreEqual(54, instance->p[numCmd][1]);
				Assert::AreEqual(67, instance->p[numCmd][2]);
				Assert::AreEqual(21, instance->p[numCmd][3]);
				Assert::AreEqual(27, instance->p[numCmd][4]);
				Assert::AreEqual(0, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(2, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(3, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(5, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(6, instance->h_WIP[numCmd][4]);
				Assert::AreEqual(8, instance->h_FIN[numCmd]);
				Assert::AreEqual(449, instance->d[numCmd]);
				Assert::AreEqual(7, instance->p_M[numCmd]);
				coord.push_back({ 239,138 });

				// Commande 5
				numCmd = 5;
				Assert::AreEqual(47, instance->p[numCmd][0]);
				Assert::AreEqual(25, instance->p[numCmd][1]);
				Assert::AreEqual(4, instance->p[numCmd][2]);
				Assert::AreEqual(66, instance->p[numCmd][3]);
				Assert::AreEqual(20, instance->p[numCmd][4]);
				Assert::AreEqual(0, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(1, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(3, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(5, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(6, instance->h_WIP[numCmd][4]);
				Assert::AreEqual(7, instance->h_FIN[numCmd]);
				Assert::AreEqual(536, instance->d[numCmd]);
				Assert::AreEqual(5, instance->p_M[numCmd]);
				coord.push_back({ 215,228 });

				// Distances
				vector<vector<int>> t;
				for (int i = 0; i < coord.size() ; i++) {
					vector<int> row;
					for (int j = 0; j < coord.size(); j++) {
						row.push_back(sqrt(pow(coord[i].first - coord[j].first, 2) + pow(coord[i].second - coord[j].second, 2)));
					}
					t.push_back(row);					
				}
				// Check
				for (int i = 0; i < instance->n + 1; i++) {
					for (int j = 0; j < instance->n + 1; j++) {
						Assert::AreEqual(t[i][j], instance->t[i][j]);
					}
				}				
			}
			catch (const std::exception& exc)
			{
				Assert::Fail(L"Exception non attendue");
			}
			delete instance;
		}

		/// <summary>
		/// Test du parseur avec un chemin invalide
		/// </summary>
		TEST_METHOD(TestInvalidPathParse)
		{
			Instance* instance = new Instance();
			try
			{
				bool result = instance->Parse("../UnitTestPRD/instanceTest/unknow.txt");
				Assert::Fail(L"Une exception d'argument invalide est attendu");
			}
			catch (const std::invalid_argument& ia) {
				
			}
			catch (const std::exception&)
			{
				Assert::Fail(L"Une exception d'argument invalide est attendu");
			}
			delete instance;
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
				Assert::AreEqual(51, inst2->p[0][0]);
				delete inst1;
				Assert::AreEqual(24, inst2->p[0][1]);
				delete inst2;
			}
			catch (exception exc) {
				cerr << exc.what();
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
				Result* res1 = new Result(instance);
				Result* res2 = new Result(*res1);
				//Assert::AreNotEqual(res1, res2);
				Assert::AreEqual(51, res2->inst->p[0][0]);
				delete res1;
				Assert::AreEqual(24, res2->inst->p[0][1]);
				delete res2;
			}
			catch (exception exc) {
				cerr << exc.what();
			}
		}
	};

	/// <summary>
	/// Test les elements de la classe Result
	/// </summary>
	TEST_CLASS(UnitTestSolverControler)
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
				Result* res1 = new Result(instance);
				Result* res2 = new Result(*res1);
				//Assert::AreNotEqual(res1, res2);
				Assert::AreEqual(51, res2->inst->p[0][0]);
				delete res1;
				Assert::AreEqual(24, res2->inst->p[0][1]);
				delete res2;
			}
			catch (exception exc) {
				cerr << exc.what();
			}
		}
	};
}
