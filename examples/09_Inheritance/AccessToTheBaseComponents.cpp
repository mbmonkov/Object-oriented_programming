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
            // ���� ������ �� ����-����� � private ������ �� ������� ����
            //m_private = 0;

            // ��� �������� ������ �� protected � public
            m_protected = 1;
            m_public = 2;
        }
};

class Third_Level_Private : public Private
{
    public:
        Third_Level_Private()
        {
            // ���� ������ �� ���� �� ������� ����
            //m_private++;
            
            // ����� �� ������, �� ��� private �����������
            // protected � public ������������ �� ������� ���� 
            // ������ ���� �� private ������ �� ����������, ����� Private
            // ������ ������ �� ��� � ����������� ����
            
            //m_protected++;
            //m_public++;
        }
};

class Protected: protected Base
{
    public:
        Protected()
        {
            // ���� ������ �� ����-����� � private ������ �� ������� ����
            //m_private = 0;

            // ��� �������� ������ �� protected � public
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

        // ����� �� ������, �� ��� protected �����������
        // protected � public ������������ �� ������� ���� 
        // ������ ���� �� protected ������ �� ����������, ����� Protected
        // ����� ������ �� ��� � ����������� ����
        
        m_protected++;
        m_public++;
    }
};

class Public: public Base
{
    public:
        Public()
        {
            // ���� ������ �� ����-����� � private ������ �� ������� ����
            //m_private = 0;

            // ��� �������� ������ �� protected � public
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

        // ����� �� ������, �� ��� public �����������
        // protected � public ������������ �� ������� ���� 
        // ������ ���� ��������� �� protected � public ������ �� ����������, ����� Public
        // ����� ������ �� ��� � ����������� ����

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
    
    // ���� �� �� �����, �� ��� private ����������� protected � public
    // ������ ���� �� private ������ �� ����������� ����
    // ���� ������ ������ �� ���
    
    //pri.m_protected = 1;
    //pri.m_public = 2;

    Protected pro;

    //pro.m_private = 0;
    
    // ��� protected ����������� protected � public
    // ������ ���� �� protected ������ �� ����������� ����
    // ���� ������ ������ �� ���
    
    //pro.m_protected = 1;
    //pro.m_public = 2;

    Public pub;
    //pub.m_private = 0;
    
    // ��� public �����������
    // protected ����-������� ������ ���� �� protected ������ �� ����������� ����,
    // ���� ������ �� ���
    //pub.m_protected = 1;

    // public ����-������� ������ ���� �� public ������ �� ����������� ����
    // ��� ������ ������ �� ���
    pub.m_public = 2;

    return 0;
}
