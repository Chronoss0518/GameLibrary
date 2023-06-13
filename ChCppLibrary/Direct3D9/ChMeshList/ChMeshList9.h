#ifndef Ch_D3D9_MeLi_h
#define Ch_D3D9_MeLi_h

class ChAnimationObject9;

namespace ChTex
{
	typedef class BaseTexture9 Texture9;
}

namespace ChMesh
{
	typedef class BaseMesh9 Mesh9;


#ifndef _ChMesh9
#define _ChMesh9

	//メッシュの頂点データ//
	struct MeshVertex9
	{
		ChVec3_9 pos;
		ChVec3_9 normal;
		D3DXVECTOR2 tex;
	};

	struct MeshFace9
	{
		unsigned long vertexNum[3];
		ChVec3_9 normal;
		ChVec3_9 centerPos;
	};

#endif

	class SkinMesh9;

	//SmpXFile専用のenum classを作って、SetSmpXFileの第二引数に入れる。//
	//以降第二引数に入れた数字を使ってSmpXFileを操作する。//
	typedef class MeshList9:public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//OperatorList//

		MeshList9& operator =(const MeshList9& _xList)
		{
			return *this;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		virtual ~MeshList9();

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//もし、XFileフォルダーなどを作っていない場合は第二引数に""を入れる。//
		inline void Init(
			const LPDIRECT3DDEVICE9 _dv
			, const std::string& _fileInDirectoryPath)
		{
			device = _dv;
			directoryPath = _fileInDirectoryPath;
			SetInitFlg(true);
		}

		inline void Release()override
		{
			if (meshList.empty())return;
			meshList.clear();
			SetInitFlg(false);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Meshの登録(DataNameを使って3Dモデルを選択する)//
		void SetMesh(
			const std::string& _meshName
			, const unsigned short _dataNum);

		//※登録できるSkinMeshがまだ完成していない//
		//SkinMeshの登録(DataNameを使って3Dモデルを選択する)//
		void SetSkinMesh(
			const std::string& _meshName
			, const unsigned short _dataNum);

		//登録されているMeshの画像を一部変更//
		void SetTexture(
			const unsigned short _dataNum
			, const unsigned long _texNum
			, const ChPtr::Shared<ChTex::Texture9> _tex);

		//SkinMesh専用//
		//XFileよりアニメーションを取得//
		void SetAnimation(
			const unsigned short _dataNum
			, const std::string& _aniamtionName
			, const std::string& _xFileName);

		//SkinMesh専用//
		//外部で作成したアニメーションをセット//
		void SetAnimation(
			const unsigned short _dataNum
			, const std::string& _aniamtionName
			, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//選択したMeshの選択した面のベースとなる法線//
		MeshFace9 GetEasyFace(
			const unsigned short _dataNum
			, const unsigned long _faseNum);

		//登録されているMeshの数//
		inline const unsigned short GetMeshSize()
		{
			return (unsigned short)meshList.size();
		}

		//登録されているMeshのマテリアルを取得//
		std::vector<ChPtr::Shared<ChMaterial_9>>& GetMeshMaterials(
			const unsigned short _dataNum);

		//描画時などに利用されるMeshを出力//
		inline ChPtr::Shared<BaseMesh9> GetMesh(const unsigned short _dataNum)
		{
			if (meshList.size() <= _dataNum)return nullptr;

			return meshList[_dataNum];
		}

		///////////////////////////////////////////////////////////////////////////////////

		//この関数を呼ぶと各面に横滑りを行うための法線が生成される。
		void CreateEasyFace(
			const unsigned short _dataNum
			, const unsigned short _baseMatNum);

		///////////////////////////////////////////////////////////////////////////////////

		//登録されているXFileをSubSetごとに描画する//
		void DrawMesh(
			const ChMat_9 &_mat
			, const unsigned short _dataNum
			, const long _subNum = -1);

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		LPDIRECT3DDEVICE9 device;

		std::string directoryPath;


		static MeshFace9 nFace;

		static std::vector<ChPtr::Shared<ChMaterial_9>> nMaterial;

		std::map<unsigned short, ChPtr::Shared<BaseMesh9>>meshList;

	}ChMeshList9;

}

#endif
//CopyRight Chronoss0518 2018/08