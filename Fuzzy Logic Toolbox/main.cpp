#include <bits/stdc++.h>
using namespace std ;
class FuzzySet
{
    public:
    string name ;
    string type ;
    vector<double> values ;
    FuzzySet( string Name , string Type,vector<double> Values )
    {
        name = Name ;
        type = Type ;
        values = Values ;
    }
};
class Variable
{
    public:
    vector<FuzzySet> Fuzzysets ;
    string name ;
    string type ;
    bool done=false;
    pair<double,double> range ;

    void addFuzzySet(string N , string T,vector<double> V )
    {
        FuzzySet set(N,T,V) ;
        Fuzzysets.push_back(set) ;
    }
    void setName( string N )
    {
        name = N ;
    }
    void setType( string T )
    {
        type = T ;
    }
    void setRange( pair<double,double> R )
    {
        range.first = R.first ;
        range.second = R.second ;
    }
};

vector<double> Fuzzification( Variable variable , double value )
{
    vector<double> MembershipDegree;
    vector<bool> degree ;
    int i = 0 , size;
    while( i < variable.Fuzzysets.size() )
    {
        size = variable.Fuzzysets[i].values.size() ;
        if( value < variable.Fuzzysets[i].values[size-1] && value > variable.Fuzzysets[i].values[0] )
        {
            degree.push_back(true) ;
        }
        else
        {
            degree.push_back(false) ;
        }
        i++ ;
    }

    if( variable.Fuzzysets[0].type == "TRAP")
    {
        for (int j = 0; j < degree.size(); j++)
        {
            double x1 , y1 , x2 , y2  ;
            double slope, y , b ;
            if( degree[j] == true  )
            {
                for (int i = 0; i < size-1; i++)
                {
                    if( value >= variable.Fuzzysets[j].values[i] && value <= variable.Fuzzysets[j].values[i+1] )
                    {
                        x1 = variable.Fuzzysets[j].values[i] ;
                        x2 = variable.Fuzzysets[j].values[i+1] ;
                        if( i == 1 || i == 2 )
                        {
                            y1 = 1 ;
                        }
                        else
                        {
                            y1 = 0 ;
                        }
                        if( i+1 == 1 || i+1 == 2 )
                        {
                            y2 = 1 ;
                        }
                        else
                        {
                            y2 = 0 ;
                        }
                        slope = (y2-y1)/(x2-x1) ;
                        b = y1 - (slope*x1) ;
                        y = slope*value + b ;
                        MembershipDegree.push_back(y) ;
                        break ;
                    }
                }
                if( j != degree.size()-1 )
                {
                    if ( degree[j+1] == true )
                    {
                        for (int i = 0; i < size-1; i++)
                        {
                            if( value >= variable.Fuzzysets[j+1].values[i] && value <= variable.Fuzzysets[j+1].values[i+1] )
                            {
                                x1 = variable.Fuzzysets[j+1].values[i] ;
                                x2 = variable.Fuzzysets[j+1].values[i+1] ;
                                if( i == 1 || i == 2 )
                                {
                                    y1 = 1 ;
                                }
                                else
                                {
                                    y1 = 0 ;
                                }
                                if( i+1 == 1 || i+1 == 2 )
                                {
                                    y2 = 1 ;
                                }
                                else
                                {
                                    y2 = 0 ;
                                }
                                slope = (y2-y1)/(x2-x1) ;
                                b = y1 - (slope*x1) ;
                                y = slope*value + b ;
                                MembershipDegree.push_back(y) ;
                                break ;
                            }
                        }
                        j += 1 ;
                    }
                }


            }
            else
            {
                MembershipDegree.push_back(0.0) ;
            }
        }
    }
    else
    {
        for (int j = 0; j < degree.size(); j++)
        {
            double x1 , y1 , x2 , y2  ;
            double slope, y , b ;
            if( degree[j] == true  )
            {
                for (int i = 0; i < size-1; i++)
                {
                    if( value >= variable.Fuzzysets[j].values[i] && value <= variable.Fuzzysets[j].values[i+1] )
                    {
                        x1 = variable.Fuzzysets[j].values[i] ;
                        x2 = variable.Fuzzysets[j].values[i+1] ;
                        if( i == 1  )
                        {
                            y1 = 1 ;
                        }
                        else
                        {
                            y1 = 0 ;
                        }
                        if( i+1 == 1  )
                        {
                            y2 = 1 ;
                        }
                        else
                        {
                            y2 = 0 ;
                        }
                        slope = (y2-y1)/(x2-x1) ;
                        b = y1 - (slope*x1) ;
                        y = slope*value + b ;
                        MembershipDegree.push_back(y) ;
                        break ;
                    }
                }
                if( j != degree.size()-1 )
                {
                    if ( degree[j+1] == true )
                    {
                        for (int i = 0; i < size-1; i++)
                        {
                            if( value >= variable.Fuzzysets[j+1].values[i] && value <= variable.Fuzzysets[j+1].values[i+1] )
                            {
                                x1 = variable.Fuzzysets[j+1].values[i] ;
                                x2 = variable.Fuzzysets[j+1].values[i+1] ;
                                if( i == 1  )
                                {
                                    y1 = 1 ;
                                }
                                else
                                {
                                    y1 = 0 ;
                                }
                                if( i+1 == 1 )
                                {
                                    y2 = 1 ;
                                }
                                else
                                {
                                    y2 = 0 ;
                                }
                                slope = (y2-y1)/(x2-x1) ;
                                b = y1 - (slope*x1) ;
                                y = slope*value + b ;
                                MembershipDegree.push_back(y) ;
                                break ;
                            }
                        }

                    }
                }


            }
            else
            {
                MembershipDegree.push_back(0.0) ;
            }
        }
    }
    return MembershipDegree ;
}

class FuzzyRule {
private:
    string rule;
    vector<double> results;
    double not_variable = -1;
    double and_variable = -2;
    double or_variable = -3;

public:
    FuzzyRule(string rule) {
        this->rule = rule;
    }
    vector<string> split_string(const string& s, const string& delimiter) {
        vector<string> tokens;
        size_t pos = 0;
        size_t found;

        while ((found = s.find(delimiter, pos)) != string::npos) {
            tokens.push_back(s.substr(pos, found - pos));
            pos = found + delimiter.size();
        }

        tokens.push_back(s.substr(pos));

        return tokens;
    }

    void solve_rule(unordered_map<string, unordered_map<string, double>> &input_memberships,
                    unordered_map<string, unordered_map<string, double>> &output_membership,
                    vector<Variable> &variables, Variable &outputVariable) {
        rule = rule.replace(rule.find("and_not"), 7, "and not");
        rule = rule.replace(rule.find("or_not"), 6, "or not");

        vector<string> splitter_rule = split_string(rule, "=> ");
        vector<string> premise = split_string(splitter_rule[0], " ");
        vector<string> conclusion = split_string(splitter_rule[1], " ");

        if (outputVariable.name == conclusion[0]) {
            if (takeRule(premise, conclusion[0], variables)) {
                substitute(premise, input_memberships);
                evaluate_operations();

                std::string variable_name = conclusion[0];
                std::string set_name = conclusion[1];

                // if two rules infer the same memberships, take the maximum one
                double old_membership = output_membership[variable_name][set_name];
                if (old_membership < results[0]) {
                    output_membership[variable_name][set_name] = results[0];
                }
            }
        }
    }

    bool takeRule(const vector<string> &premise, const string &conclusion,const vector<Variable> &variables) {
        int check_premise = 0;
        int variablesCounter = 0;

        // check if the variables on the left-hand side are ready as input
        for (const auto &var: premise) {
            for (const auto &variable: variables) {
                if (var == variable.name) {
                    variablesCounter++;
                    if (variable.type == "IN" || (variable.type == "OUT" && variable.done == true)) {
                        check_premise++;
                    }
                }
            }
        }
        if (check_premise == variablesCounter) {
            return true;
        }

        // do not take this rule, it is not ready yet
        return false;
    }

    void substitute(const vector<std::string> &premise,
                    const unordered_map<std::string,unordered_map<string, double>> &input_memberships) {
        for (size_t i = 0; i < premise.size(); i++) {
            double result = 0.0;
            if (premise[i] == "not") {
                result = not_variable;
            } else if (premise[i] == "and") {
                result = and_variable;
            } else if (premise[i] == "or") {
                result = or_variable;
            } else if (i + 1 < premise.size()) {
                result = input_memberships.at(premise[i]).at(premise[i + 1]);
                i++;
            }
            results.push_back(result);
        }
    }

    void evaluate_operations() {
        evaluate_not();
        evaluate_and();
        evaluate_or();
    }

    void evaluate_not() {
        for (size_t i = 0; i < results.size(); i++) {
            if (results[i] == not_variable) {
                double result = 1 - results[i + 1];
                results[i] = result;
                results.erase(results.begin() + i + 1);
            }
        }
    }

    void evaluate_and() {
        for (size_t i = 0; i < results.size(); i++) {
            if (results[i] == and_variable) {
                double left_operand = results[i - 1];
                double right_operand = results[i + 1];
                double result = min(left_operand, right_operand);
                results[i - 1] = result;
                results.erase(results.begin() + i);
                results.erase(results.begin() + i);
                i--;
            }
        }
    }

    void evaluate_or() {
        for (size_t i = 0; i < results.size(); i++) {
            if (results[i] == or_variable) {
                double left_operand = results[i - 1];
                double right_operand = results[i + 1];
                double result = max(left_operand, right_operand);
                results[i - 1] = result;
                results.erase(results.begin() + i);
            }
        }
    }
};

class Defuzzification
{
public:
    static double TrapCentroid(const vector<double>& xvalues)
    {
        int n = xvalues.size();
        if (n != 4)
        cout<<"Error, The trapezoid requires exactly 4 points."<<endl;

        vector<double>yvalues;
        for (int i = 0; i <= n-1; ++i)
        {
          yvalues.push_back(i);
        }
        //A (signed area) = 1/2 ∑(xiyi+1 − xi+1yi)
        double signed_area = 0.5 * (
        (xvalues[0] * yvalues[1] - xvalues[1] * yvalues[0]) +
        (xvalues[1] * yvalues[2] - xvalues[2] * yvalues[1]) +
        (xvalues[2] * yvalues[3] - xvalues[3] * yvalues[2]) +
        (xvalues[3] * yvalues[0] - xvalues[0] * yvalues[3])
        );
        //Cx = 1/6A ∑(xi + xi+1)(xiyi+1 − xi+1yi)
        double centroid_sum = 0;
        for (int i = 0; i <= n - 1; ++i)
        {
        double term = (xvalues[i] + xvalues[i + 1]) * (xvalues[i] * yvalues[i + 1] - xvalues[i + 1] * yvalues[i]);
        centroid_sum = centroid_sum + term;
        }

        double centroid = centroid_sum / (6 * signed_area);
        return centroid;

    }

    static double TriangleCentroid(const vector<double>&values)
    {
        int n = values.size();
        if (n != 3)
        cout<<"Error, The triangle requires exactly 3 points."<<endl;
        double sum=0.0;
        for(int i=0;i<n;i++)
        {
            sum = sum + values[i];
        }
        return sum/3.0;
    }

    static double weightedAverage(const vector<double>& membershipValues, vector<double>& centroids)
    {
        double summ = 0.0;
        double Memberships = 0.0;

        for (size_t i = 0; i < membershipValues.size(); ++i)
        {
            //double Area = centroidFunction(outputVariable.Fuzzysets[i]);
            summ = summ +  membershipValues[i] * centroids[i];
            Memberships = Memberships + membershipValues[i];
        }
        if (Memberships==0.0)
        {
            return 0.0;
        }
        return summ/Memberships;
    }
};






//Mn awl hna el5twat bta3t el console

//da el class el hyrbot ben kol el functions
class AllFunctions
{

public:
    vector<Variable> SystemVariables ;
    vector<Variable> SystemVariablesIN;
    vector<Variable> SystemVariablesOUT;
    void addVariables();
    void addFuzzySets();
    void addRules();
    void runSimulationOnCrisp();

};

//Function to add variable's name and type (IN/OUT) and range ([lower, upper]) --> 1
void AllFunctions:: addVariables()
{

    cout<<"Enter the variable's name, type (IN/OUT) and range ([lower, upper]):\n"
          "(Press x to finish)\n"
          "--------------------------------------------------------------------\n";

    string typing;
    while(true)
    {
        string type ;
        pair<double,double> range ;
        bool IN = false;
        bool OUT = false;
        cin>>typing;
        if (typing == "x")
            break;
        else
        {
            cin >> type ;
            if(type== "IN")
            IN  = true;
            if(type== "OUT")
            OUT = true;

            cin >> range.first >> range.second ;
            if(range.first>range.second)
            {
                cout<<"Error, Invalid values! Insert the values again"<<endl;
                continue;
            }
            Variable v ;
            v.setName(typing) ;
            v.setType(type) ;
            v.setRange(range) ;

            if(IN && !OUT)
            {
                SystemVariablesIN.push_back(v);
            }
            else if(OUT && !IN)
            {
                SystemVariablesOUT.push_back(v);
            }

        }

    }

}


//function to add fuzzy sets to existing variable and add it's type (TRI/TRAP) and values -->  2
void AllFunctions:: addFuzzySets()
{
    bool found = false ;
    int i ;
    Variable v ;
    cout<<"Enter the variable's name:\n"
            "--------------------------\n\n";
    string variableName;
    cin>>variableName;

    for (i = 0; i < SystemVariables.size(); i++)
    {
        if( variableName == SystemVariablesIN[i].name ||  variableName == SystemVariablesOUT[i].name )
        {
            found = true ;
            break ;
        }
    }
    if( !found )
    {
        cout << "Error, this variable name not exists"<<endl;
        return;
    }

    cout<<"Enter the fuzzy set name, type (TRI/TRAP) and values: (Press x to finish)\n"
            "-----------------------------------------------------\n\n";

    while(true)
    {
        string typing;
        cin>>typing;
        if (typing == "x")
            break;

        string setName = typing;
        typing = "";

        string type;
        cin>>type;

        vector<double>points;
        double point1, point2, point3, point4;
        if(type == "TRI")
        {
            cin>>point1 >> point2 >> point3;
            if(point2 < point1 || point3 < point1 || point3 < point2)
            {
                cout<<"Error, Invalid values! Insert the values again"<<endl;
                continue;
            }
            points={point1,point2,point3};
        }

        else if (type == "TRAP")
        {
            cin>>point1 >> point2 >> point3 >> point4;
            if(point4 < point1 || point4 < point2 || point4 < point3 || point2 < point1 || point3 < point1 || point3 < point2)
            {
                cout<<"Error, Invalid values! Insert the values again"<<endl;
                continue;
            }
            points={point1,point2,point3,point4};
        }
        else
        {
            cout<<"Error, Wrong type! Write valid type"<<endl;
            continue;
        }

        SystemVariables[i].addFuzzySet(setName, type, points) ;
    }
}

//Function to add rules
void AllFunctions:: addRules()
{
      cout<<"Enter the rules in this format: (Press x to finish)\n"
          "IN_variable set operator IN_variable set => OUT_variable set\n"
          "------------------------------------------------------------\n";

    while(true)
    {
        string typing;
        cin >> typing;
        if(typing == "x")
            break;
        else
        {
        //--------
        }
    }
}

//function to run simulation on crisp  value
void AllFunctions:: runSimulationOnCrisp()
{

}

void MainMenu()
{
    AllFunctions obj;
    cout<<"Enter the system's name and a brief description:\n"
          "------------------------------------------------\n";
    string system_name;
    cin>>system_name;

    string Typing;
    cin>>Typing;
    string description = "";
    description = description + Typing;

    while( Typing[ Typing.size()-1] != '.')
    {
        cin>>Typing;
        description = description + Typing;
    }
    string choice;
    cout<<endl;
    while (true)
    {
        cout<<"Main Menu:\n"
                "==========\n"
                "1- Add variables.\n"
                "2- Add fuzzy sets to an existing variable.\n"
                "3- Add rules.\n"
                "4- Run the simulation on crisp values.\n\n";

        cin>>choice;
        if (choice == "1"){
            obj.addVariables();
        }

        else if (choice == "2"){
            obj.addFuzzySets();
        }

        else if (choice == "3"){
            obj.addRules();
        }

        else if (choice == "4"){
           obj.runSimulationOnCrisp();
        }

        else
        {
            cout<<"Error, No choice exists!"<<endl;
        }

    }

}

void FuzzyToolBox()
{
    int num;
    while(true)
    {
        cout<<"Fuzzy Logic Toolbox\n"
            <<"===================\n"
            <<"1- Create a new fuzzy system\n"
            <<"2- Quit\n\n";
        cin>>num;
        if(num == 1)
            MainMenu();
        else
            break;
    }
}


int main()
{
    FuzzyToolBox();
    return 0;
}
