#include "pch.h"
#include "CppUnitTest.h"
#include "../PRD/Instance.cpp"
#include <string>

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
				Assert::AreEqual(true, result,L"Aucun problème n'est attendu");
				
				// Premiers parametres
				Assert::AreEqual(6, instance->n);
				Assert::AreEqual(5, instance->m);				
				Assert::AreEqual(4000, instance->c_V);
				Assert::AreEqual(2, instance->id);			

				// Commande 0
				int numCmd = 0;
				Assert::AreEqual(51, instance->p[numCmd][0]);
				Assert::AreEqual(24, instance->p[numCmd][1]);
				Assert::AreEqual(85, instance->p[numCmd][2]);
				Assert::AreEqual(45, instance->p[numCmd][3]);
				Assert::AreEqual(17, instance->p[numCmd][4]);
				Assert::AreEqual(2, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(4, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(6, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(7, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(9, instance->h_FIN[numCmd]);
				Assert::AreEqual(71, instance->d[numCmd]);
				Assert::AreEqual(9, instance->p_M[numCmd]);
				Assert::AreEqual(149, instance->t[numCmd][0]);
				Assert::AreEqual(154, instance->t[numCmd][1]);

				// Commande 1
				numCmd = 1;
				Assert::AreEqual(1, instance->p[numCmd][0]);
				Assert::AreEqual(99, instance->p[numCmd][1]);
				Assert::AreEqual(35, instance->p[numCmd][2]);
				Assert::AreEqual(64, instance->p[numCmd][3]);
				Assert::AreEqual(7, instance->p[numCmd][4]);
				Assert::AreEqual(1, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(2, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(4, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(5, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(6, instance->h_FIN[numCmd]);
				Assert::AreEqual(91, instance->d[numCmd]);
				Assert::AreEqual(9, instance->p_M[numCmd]);
				Assert::AreEqual(128, instance->t[numCmd][0]);
				Assert::AreEqual(129, instance->t[numCmd][1]);

				// Commande 2
				numCmd = 2;
				Assert::AreEqual(53, instance->p[numCmd][0]);
				Assert::AreEqual(94, instance->p[numCmd][1]);
				Assert::AreEqual(8, instance->p[numCmd][2]);
				Assert::AreEqual(79, instance->p[numCmd][3]);
				Assert::AreEqual(78, instance->p[numCmd][4]);
				Assert::AreEqual(1, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(3, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(4, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(6, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(7, instance->h_FIN[numCmd]);
				Assert::AreEqual(123, instance->d[numCmd]);
				Assert::AreEqual(10, instance->p_M[numCmd]);
				Assert::AreEqual(153, instance->t[numCmd][0]);
				Assert::AreEqual(283, instance->t[numCmd][1]);

				// Commande 3
				numCmd = 3;
				Assert::AreEqual(13, instance->p[numCmd][0]);
				Assert::AreEqual(8, instance->p[numCmd][1]);
				Assert::AreEqual(84, instance->p[numCmd][2]);
				Assert::AreEqual(76, instance->p[numCmd][3]);
				Assert::AreEqual(52, instance->p[numCmd][4]);
				Assert::AreEqual(1, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(2, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(3, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(5, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(6, instance->h_FIN[numCmd]);
				Assert::AreEqual(441, instance->d[numCmd]);
				Assert::AreEqual(9, instance->p_M[numCmd]);
				Assert::AreEqual(103, instance->t[numCmd][0]);
				Assert::AreEqual(234, instance->t[numCmd][1]);

				// Commande 4
				numCmd = 4;
				Assert::AreEqual(86, instance->p[numCmd][0]);
				Assert::AreEqual(54, instance->p[numCmd][1]);
				Assert::AreEqual(67, instance->p[numCmd][2]);
				Assert::AreEqual(21, instance->p[numCmd][3]);
				Assert::AreEqual(27, instance->p[numCmd][4]);
				Assert::AreEqual(2, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(3, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(5, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(6, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(8, instance->h_FIN[numCmd]);
				Assert::AreEqual(449, instance->d[numCmd]);
				Assert::AreEqual(7, instance->p_M[numCmd]);
				Assert::AreEqual(239, instance->t[numCmd][0]);
				Assert::AreEqual(138, instance->t[numCmd][1]);

				// Commande 5
				numCmd = 5;
				Assert::AreEqual(47, instance->p[numCmd][0]);
				Assert::AreEqual(25, instance->p[numCmd][1]);
				Assert::AreEqual(4, instance->p[numCmd][2]);
				Assert::AreEqual(66, instance->p[numCmd][3]);
				Assert::AreEqual(20, instance->p[numCmd][4]);
				Assert::AreEqual(1, instance->h_WIP[numCmd][0]);
				Assert::AreEqual(3, instance->h_WIP[numCmd][1]);
				Assert::AreEqual(5, instance->h_WIP[numCmd][2]);
				Assert::AreEqual(6, instance->h_WIP[numCmd][3]);
				Assert::AreEqual(7, instance->h_FIN[numCmd]);
				Assert::AreEqual(536, instance->d[numCmd]);
				Assert::AreEqual(5, instance->p_M[numCmd]);
				Assert::AreEqual(215, instance->t[numCmd][0]);
				Assert::AreEqual(228, instance->t[numCmd][1]);
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
	};
}
