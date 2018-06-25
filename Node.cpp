#include "Node.h" 

std::string Node::PrintRely()
{
	std::string ans=name+" rely on:\n";
	std::set<std::string> lib;
	lib.clear();
	Rely(lib);
	if(lib.empty())ans+="\tNOTHING\n";
	for(auto it=lib.cbegin();it!=lib.cend();it++) 
		ans+="\t"+*it+"\n";
	return ans;
}

Tensor Node::Eval(std::map<std::string,Tensor>&Inputs)
{
	Tensor ans=eval(Inputs);
	Release();
	return ans;
}

Tensor Node::Eval(const std::initializer_list<std::pair<std::string,Tensor>>& il)
{
	std::map<std::string,Tensor> Inputs;
	for(auto it=il.begin();it!=il.end();it++)
	{
		if(Inputs.find(it->first)!=Inputs.end())
			throw std::invalid_argument("Error : Redeclaration in inputs!");
		Inputs[it->first]=it->second;
	}
	return Eval(Inputs);
}
