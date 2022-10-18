// An AVL tree node
template <class T>
class NodeAVL {
    public:
        NodeAVL *right;
        NodeAVL *left;
        NodeAVL *parent;
        T* data;
        int fe; // factor de equilibrio
        int height;
        int heightLeft;
        int heightRight;
    
    public:
        NodeAVL() {
            data = nullptr;
            right = nullptr;
            left = nullptr;
            parent = nullptr;
            fe = 0;
            height = 1;
            heightLeft = 0;
            heightRight = 0;
        }

        NodeAVL(T *pData) {
            data = pData;
            right = nullptr;
            left = nullptr;
            parent = nullptr;
            fe = 0;
            height = 1;
            heightLeft = 0;
            heightRight = 0;
        }

        T* getData() {
            return data;
        }

        void setData(T *pData) {
            this->data = pData;
        }

        void setRight(NodeAVL *pNode){
            right = pNode;
        }

        NodeAVL* getRight(){
            return right;
        }

        void setLeft(NodeAVL *pNode){
            left = pNode;
        }

        NodeAVL* getLeft(){
            return left;
        }

        void setParent(NodeAVL *pNode){
            parent = pNode;
        }

        NodeAVL* getParent(){
            return parent;
        }

        void setFE(int pFE){
            fe = pFE;
        }

        int getFE(){
            return fe;
        }

        int decFE(){
            return --fe;
        }

        int incFE(){
            return ++fe;
        }

        void setHeight(int pHeight){
            height = pHeight;
        }

        int getHeight(){
            return height;
        }

        void setHeightLeft(int pHeightLeft){
            heightLeft = pHeightLeft;
        }

        int getHeightLeft(){
            return heightLeft;
        }

        void setHeightRight(int pHeightRight){
            heightRight = pHeightRight;
        }

        int getHeightRight(){
            return heightRight;
        }
};