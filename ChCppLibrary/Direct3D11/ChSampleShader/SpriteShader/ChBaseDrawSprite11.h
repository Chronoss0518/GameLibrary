#ifndef Ch_D3D11_SS_BaseSprite_h
#define Ch_D3D11_SS_BaseSprite_h

#include"../ChSampleShaderBase11.h"


namespace ChD3D11
{

	class Sprite11;

	namespace Shader
	{

		class BaseDrawSprite11 final :public SampleShaderBase11
		{
		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release();

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public://Set Functions//

			void SetSpriteMatrix(const ChLMat& _mat);

			inline void SetAlphaBlendFlg(const ChStd::Bool _flg) { alphaBlendFlg = _flg; }

		public://Get Functions//

			inline ChLMat GetSpriteMatrix() { return spriteData.GetSpriteMatrix(); }

		public://Other Functions//

		//�ʏ�`��//
			void Draw(
				ID3D11DeviceContext* _dc
				, TextureBase11& _tex
				, Sprite11& _sprite
				, const ChMat_11& _mat = ChMat_11());

		private:

		private://Member Value//

			CB::CBSprite11 spriteData;

			VertexBuffer11<Ch3D::Vertex> vertexBuffer;
			IndexBuffer11 indexBuffer;

			ChStd::Bool alphaBlendFlg = false;

		};
	}
}



#endif