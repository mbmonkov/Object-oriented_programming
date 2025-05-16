#include <iostream>

class Base
{
    private:
        int m_private;
        void private_function() {}

    protected:
        int m_protected;
        void protected_function() {}

    public:
        int m_public;
        void public_function() {}
};

class Private: private Base
{
    public:
        Private()
        {
            // няма достъп до член-данни в private частта на базовия клас
            //m_private = 0;

            // има директен достъп до protected и public
            m_protected = 1;
            m_public = 2;
        }
};

class Third_Level_Private : public Private
{
    public:
        Third_Level_Private()
        {
            // няма достъп до нищо от базовия клас
            //m_private++;
            
            // можем да мислим, че при private наследяване
            // protected и public компонентите на базовия клас 
            // стават част от private частта на наследника, класа Private
            // нямаме достъп до тях в производния клас
            
            //m_protected++;
            //m_public++;
        }
};

class Protected: protected Base
{
    public:
        Protected()
        {
            // няма достъп до член-данни в private частта на базовия клас
            //m_private = 0;

            // има директен достъп до protected и public
            m_protected = 1;
            m_public = 2;
        }
};

class Third_Level_Protected : public Protected
{
public:
    Third_Level_Protected()
    {
        // m_private++;

        // можем да мислим, че при protected наследяване
        // protected и public компонентите на базовия клас 
        // стават част от protected частта на наследника, класа Protected
        // имаме достъп до тях в производния клас
        
        m_protected++;
        m_public++;
    }
};

class Public: public Base
{
    public:
        Public()
        {
            // няма достъп до член-данни в private частта на базовия клас
            //m_private = 0;

            // има директен достъп до protected и public
            m_protected = 1;
            m_public = 2;
        }
};

class Third_Level_Public : public Public
{
public:
    Third_Level_Public()
    {
        // m_private++;

        // можем да мислим, че при public наследяване
        // protected и public компонентите на базовия клас 
        // стават част съответно от protected и public частта на наследника, класа Public
        // Имаме достъп до тях в производния клас

        m_protected++;
        m_public++;
    }
};

int main()
{
    Base b;
    b.m_public = 10;
    b.public_function();

    Private pri;
    //pri.m_private = 0;
    
    // може да се мисли, че при private наследяване protected и public
    // стават част от private частта на производния клас
    // няма външен достъп до тях
    
    //pri.m_protected = 1;
    //pri.m_public = 2;

    Protected pro;

    //pro.m_private = 0;
    
    // при protected наследяване protected и public
    // стават част от protected частта на производния клас
    // няма външен достъп до тях
    
    //pro.m_protected = 1;
    //pro.m_public = 2;

    Public pub;
    //pub.m_private = 0;
    
    // при public наследяване
    // protected член-данните стават част от protected частта на производния клас,
    // няма достъп до тях
    //pub.m_protected = 1;

    // public член-данните стават част от public частта на производния клас
    // има външен достъп до тях
    pub.m_public = 2;

    return 0;
}
