#include "SolverControler.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include <tchar.h>

/// <summary>
/// Check if a file end with a specific suffix
/// </summary>
/// <param name="str">String to check</param>
/// <param name="suffix">Suffix to found at the end</param>
/// <returns>True for yes</returns>
bool has_suffix(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

wchar_t* charArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

string LPCWSTRtoString(wchar_t* txt) {
    wstring ws(txt);
    return string(ws.begin(), ws.end());
}

SolverControler::SolverControler()
{
    solver = NULL;
    results = list<Result*>();
    instances = list<Instance*>();
}

SolverControler::~SolverControler()
{
    if (solver != NULL)
        delete solver;

    for (Result* res : results) {
        if (res != NULL)
            delete res;
    }
    results.clear();

    for (Instance* inst : instances) {
        if (inst != NULL)
            delete inst;
    }
    instances.clear();
}

void SolverControler::LaunchComputation()
{
    if (solver != NULL && instances.size() != 0) {
        for (Instance* inst : instances) {
            solver->setNewInstance(inst);
            Result* res = solver->Solve();
            results.push_back(res);
        }
    }   
}

bool SolverControler::ImportInstances(string dir)
{
    std::string pattern(dir);
    pattern.append("\\*");
    WIN32_FIND_DATA data;
    HANDLE hFind;
    if ((hFind = FindFirstFile(charArrayToLPCWSTR(pattern.c_str()), &data)) != INVALID_HANDLE_VALUE) {
        do {
            if (has_suffix(LPCWSTRtoString(data.cFileName), ".txt")) {
                try {
                    Instance* inst = new Instance(dir + "\\" + LPCWSTRtoString(data.cFileName));
                    instances.push_back(inst);
                }
                catch (exception exc) {
                    // cout << "Error : " << exc.what();
                    return false;
                }
            }
        } while (FindNextFile(hFind, &data) != 0);
        FindClose(hFind);
    }
    return true;
}

bool SolverControler::ExportResults(string path)
{
    // No results
    if (results.size() == 0)
        return false;

    // Check if file already exist
    ifstream file;
    file.open(path);
    if (file) {
        cout << "Error when saving results : File already exist";
        return false;
    }

    // Check extension
    if (!has_suffix(path, ".txt")) {
        cout << "Error when saving results : need .txt extension";
        return false;
    }

    // Saving
    try {
        string sep = " ";
        ofstream output(path);
        for (Result* res : results) {
            output << res->inst->id << sep << res->inst->n << sep << res->cout_total << sep << res->IC_WIP << sep << res->IC_FIN << sep << res->PPC_M << endl;
        }
        output.close();
        return true;
    }
    catch (exception e) {
        cout << e.what();
        return false;
    }
}

void SolverControler::Reset()
{
    if (solver != NULL)
        delete solver;

    for (Result* res : results) {
        if (res != NULL)
            delete res;
    }
    results.clear();

    for (Instance* inst : instances) {
        if (inst != NULL)
            delete inst;
    }
    instances.clear();
}

