class Camera
{
    public:
        static Camera& getInstance()
        {
            static Camera    instance;
            return instance;
        }
    private:
        Camera() {};
        Camera(Camera const&);
        void operator=(Camera const&);
};
