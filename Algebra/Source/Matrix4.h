#pragma once
#include <vector>

namespace Algebra
{
	class Matrix4
	{
	private:
		float m_Matrix[4][4] = { 0 };
	public:
		Matrix4() {}
		Matrix4(std::vector<std::vector<float>> values)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m_Matrix[i][j] = values[i][j];
				}
			}
		}
	};
}