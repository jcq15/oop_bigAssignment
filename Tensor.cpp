
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "Tensor.h"

Tensor& Tensor::operator =(const Tensor& a)
{
	if(ismat)
	{
		for(int i=0;i<n;i++)delete[] matrix[i];
		delete[] matrix;
		matrix=nullptr;
		n=m=0;ismat=false;
	}else
		value=0;
	if(a.ismat)
	{
		n=a.n;m=a.m;
		matrix=new double*[n];
		for(int i=0;i<n;i++)
			matrix[i]=new double[m];
		ismat=true;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				matrix[i][j]=a.matrix[i][j];
	}else
		value=a.value;
	return *this;
}

Tensor& Tensor::operator+=(const Tensor& a)
{
	if(ismat!=a.ismat||(ismat&&(n!=a.n||m!=a.m)))
		throw std::invalid_argument("Error : \""+PrintType()+"+="+a.PrintType()+"\" is not permitted!");
	if(ismat)
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				matrix[i][j]+=a.matrix[i][j];
	}else
		value+=a.value;
	return *this;
}

Tensor& Tensor::operator -=(const Tensor& a)
{
	if(ismat!=a.ismat||(ismat&&(n!=a.n||m!=a.m)))
		throw std::invalid_argument("Error : \""+PrintType()+"-="+a.PrintType()+"\" is not permitted!");
	if(ismat)
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				matrix[i][j]-=a.matrix[i][j];
	}else
		value-=a.value;
	return *this;
}

Tensor& Tensor::operator /=(const Tensor& a)
{
	if(a.ismat)
		throw std::invalid_argument("Error : \""+PrintType()+"/="+a.PrintType()+"\" is not permitted!");
	if(ismat)
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				matrix[i][j]/=a.value;
	}else
		value/=a.value;
	return *this;
}

Tensor& Tensor::operator *=(const Tensor& a)
{
	if(a.ismat&&(!ismat||a.n!=a.m))
		throw std::invalid_argument("Error : \""+PrintType()+"*="+a.PrintType()+"\" is not permitted!");
	if(a.ismat&&(m!=a.n))
		throw std::invalid_argument("Error : \""+PrintType()+"*="+a.PrintType()+"\" is not permitted!");
	if(ismat)
	{
		if(a.ismat)
		{
			double **u=new double*[n];
			for(int i=0;i<n;i++)
				u[i]=new double[m];
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					for(int k=0;k<m;k++)
						u[i][j]+=matrix[i][k]*a.matrix[k][j];
			for(int i=0;i<n;i++)delete[] matrix[i];
			delete[] matrix;
			matrix=u;u=nullptr;
		}
		else 
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					matrix[i][j]*=a.value;
	}else
		value*=a.value;
	return *this;
}

double Tensor::Value()const
{
	if(ismat)
		throw std::runtime_error("Error : Try to get a value from Tensor(Matrix)!");
	return value;
}

double** Tensor::Matrix()const
{
	if(!ismat)
		throw std::runtime_error("Error : Try to get a matrix from Tensor(Number)!");
	double** res=new double*[n];
	for(int i=0;i<n;i++)
	{
		res[i]=new double[m];
		for(int j=0;j<m;j++)
			res[i][j]=matrix[i][j];
	}
	return res;
}

std::string Tensor::PrintType()const
{
	if(ismat)
		return "Matrix("+std::to_string(n)+"*"+std::to_string(m)+")";
	else 
		return "Number";
}

std::string Tensor::Print(int cnt)const
{
	if(cnt>6||cnt<0)
		throw std::invalid_argument("Error : Precision = "+std::to_string(cnt)+" is not permitted");
	if(ismat)
	{
		std::string res="";
		for(int i=0;i<n;i++)
		{
			res+="|";
			for(int j=0;j<m;j++)
			{
				std::string s(std::to_string(matrix[i][j]));
				res+=s.substr(0,s.length()-(6-(cnt==0?-1:cnt)))+"\t";
			}
			res+="|\n";
		}
		return res;
	}else
	{
		std::string s(std::to_string(value));
		return s.substr(0,s.length()-(6-(cnt==0?-1:cnt)));
	}
}

Tensor operator +(const Tensor& a,const Tensor& b)
{
	if(a.ismat!=b.ismat||(a.ismat&&(a.n!=b.n||a.m!=b.m)))
		throw std::invalid_argument("Error : \""+a.PrintType()+"+"+b.PrintType()+"\" is not permitted!");
	Tensor ans(a);
	ans+=b;
	return ans;
}

Tensor operator -(const Tensor& a,const Tensor& b)
{
	if(a.ismat!=b.ismat||(a.ismat&&(a.n!=b.n||a.m!=b.m)))
		throw std::invalid_argument("Error : \""+a.PrintType()+"-"+b.PrintType()+"\" is not permitted!");
	Tensor ans(a);
	ans-=b;
	return ans;
}
Tensor operator *(const Tensor& a,const Tensor& b)
{
	if(a.ismat!=b.ismat)
	{
		if(a.ismat)
		{
			Tensor ans(a);
			ans*=b;
			return ans;
		}else
		{
			Tensor ans(b);
			ans*=a;
			return ans;
		}
	}
	if(!a.ismat)
	{
		Tensor ans(a);
		ans*=b;
		return ans;
	}
	if(a.m!=b.n)
		throw std::invalid_argument("Error : \""+a.PrintType()+"*"+b.PrintType()+"\" is not permitted!");
	Tensor ans(a.n,b.m);
	for(int i=0;i<a.n;i++)
		for(int j=0;j<b.m;j++)
			for(int k=0;k<a.m;k++)
				ans.matrix[i][j]+=a.matrix[i][k]*b.matrix[k][j];
	return ans;
}

Tensor operator /(const Tensor& a,const Tensor& b)
{
	if(b.ismat)
		throw std::invalid_argument("Error : \""+a.PrintType()+"/"+b.PrintType()+"\" is not permitted!");
	Tensor ans(a);
	ans/=b;
	return ans;
}

Tensor exp(const Tensor& a)
{
	Tensor ans(a);
	if(ans.ismat)
	{
		for(int i=0;i<ans.n;i++)
			for(int j=0;j<ans.m;j++)
				ans.matrix[i][j]=exp(a.matrix[i][j]);
	}else
		ans.value=exp(a.value);
	return ans;
}
Tensor ln(const Tensor& a)
{
	Tensor ans(a);
	if(ans.ismat)
	{
		for(int i=0;i<ans.n;i++)
			for(int j=0;j<ans.m;j++)
				ans.matrix[i][j]=log(a.matrix[i][j]);
	}else
		ans.value=log(a.value);
	return ans;
}

Tensor sin(const Tensor& a)
{
	Tensor ans(a);
	if(ans.ismat)
	{
		for(int i=0;i<ans.n;i++)
			for(int j=0;j<ans.m;j++)
				ans.matrix[i][j]=sin(a.matrix[i][j]);
	}else
		ans.value=sin(a.value);
	return ans;
}

Tensor cos(const Tensor& a)
{
	Tensor ans(a);
	if(ans.ismat)
	{
		for(int i=0;i<ans.n;i++)
			for(int j=0;j<ans.m;j++)
				ans.matrix[i][j]=cos(a.matrix[i][j]);
	}else
		ans.value=cos(a.value);
	return ans;
}

Tensor tan(const Tensor& a)
{
	Tensor ans(a);
	if(ans.ismat)
	{
		for(int i=0;i<ans.n;i++)
			for(int j=0;j<ans.m;j++)
				ans.matrix[i][j]=tan(a.matrix[i][j]);
	}else
		ans.value=tan(a.value);
	return ans;
}

Tensor asin(const Tensor& a)
{
	Tensor ans(a);
	if(ans.ismat)
	{
		for(int i=0;i<ans.n;i++)
			for(int j=0;j<ans.m;j++)
				ans.matrix[i][j]=asin(a.matrix[i][j]);
	}else
		ans.value=asin(a.value);
	return ans;
}

Tensor acos(const Tensor& a)
{
	Tensor ans(a);
	if(ans.ismat)
	{
		for(int i=0;i<ans.n;i++)
			for(int j=0;j<ans.m;j++)
				ans.matrix[i][j]=acos(a.matrix[i][j]);
	}else
		ans.value=acos(a.value);
	return ans;
}

Tensor atan(const Tensor& a)
{
	Tensor ans(a);
	if(ans.ismat)
	{
		for(int i=0;i<ans.n;i++)
			for(int j=0;j<ans.m;j++)
				ans.matrix[i][j]=atan(a.matrix[i][j]);
	}else
		ans.value=atan(a.value);
	return ans;
}
Tensor pow(const Tensor& a,double b)
{
	Tensor ans(a);
	if(a.ismat)
	{
		for(int i=0;i<ans.n;i++)
			for(int j=0;j<ans.m;j++)
				ans.matrix[i][j]=pow(ans.matrix[i][j],b);
	}else
		ans.value=pow(ans.value,b);
	return ans;
}
Tensor pow(const Tensor& a,const Tensor& b)
{
	if(b.ismat)
		throw std::invalid_argument("Error : \"pow("+a.PrintType()+","+b.PrintType()+")\" is not permitted!");
	return pow(a,b.value);
}

void swap(Tensor& a,Tensor& b)
{
	Tensor c=std::move(a);
	a=std::move(b);
	b=std::move(c);
}
