
#pragma once

#include <chrono>

#include <glbinding/gl/types.h>

#include <globjects/globjects_api.h>
#include <globjects/Object.h>


namespace globjects
{


/** \brief Encapsulates a GL Query object
    
    A Query object is used to query different aspects of the rendering 
    pipeline, such as passed samples, generated primitives, written transform
    feedback primitives or elapsed time. With begin() and end(), the scope of 
    the measurements could be specified. As a Query object queries the GPU 
    asynchroneously, the result won't be available right after the end() 
    invokation. The resultAvailable() method indicates whether the calling of
    get()/get64() will return the final result. To wait until the result is 
    available, the wait() method can be used. Alternatively there are 
    waitAndGet() and waitAndGet64() to query the result in one invokation.
    
    There is a convenience method to create a Query object which answeres with
    the current timestamp on the GPU named timestamp() (see example below).

    An example time measurement:
    \code{.cpp}

        Query * query = new Query(gl::GL_TIME_ELAPSED);
        query->begin();
    
        // more GL calls
    
        query->end();
    
        query->wait();
        gl::GLuint timeElapsed = query->get();
        // Note: sometimes it's important to use the 64 bit equivalent, because the 32 bit version can only capture time up to 4 seconds.

    \endcode
    
    An example timestamp access:
    \code{.cpp}

        // GL calls
    
        Query * query = Query::timestamp();
    
        // even more GL calls
    
        query->wait();
        gl::GLuint64 timestamp = query->get64();
        // Note: the result is the timestamp on the GPU right after the first GL calls finished and before the second calls started.

    \endcode
    
    \see http://www.opengl.org/wiki/Query_Object
    \see http://www.opengl.org/registry/specs/ARB/timer_query.txt
 */
class GLOBJECTS_API Query : public Object
{
public:
    Query();
    virtual ~Query();

    static std::shared_ptr<Query> fromId(gl::GLuint id);

    static std::shared_ptr<Query> current(gl::GLenum target);
    static std::shared_ptr<Query> timestamp();
	
    static gl::GLint get(gl::GLenum target, gl::GLenum pname);
    static gl::GLint getIndexed(gl::GLenum target, gl::GLuint index, gl::GLenum pname);

    static gl::GLint getCounterBits(gl::GLenum target);

    virtual void accept(ObjectVisitor& visitor) override;

    void begin(gl::GLenum target) const;
    void end(gl::GLenum target) const;

    void beginIndexed(gl::GLenum target, gl::GLuint index) const;
    void endIndexed(gl::GLenum target, gl::GLuint index) const;
	
    static bool isQuery(gl::GLuint id);

    gl::GLuint get(gl::GLenum pname) const;
    gl::GLuint64 get64(gl::GLenum pname) const;
	
	bool resultAvailable() const;
    void wait() const;
    void wait(const std::chrono::duration<int, std::nano> & timeout) const;
	
    gl::GLuint waitAndGet(gl::GLenum pname) const;
    gl::GLuint64 waitAndGet64(gl::GLenum pname) const;

    gl::GLuint waitAndGet(const std::chrono::duration<int, std::nano> & timeout, gl::GLenum pname) const;
    gl::GLuint64 waitAndGet64(const std::chrono::duration<int, std::nano> & timeout, gl::GLenum pname) const;

    gl::GLuint waitAndGet(gl::GLenum pname, const std::chrono::duration<int, std::nano> & timeout) const;
    gl::GLuint64 waitAndGet64(gl::GLenum pname, const std::chrono::duration<int, std::nano> & timeout) const;
	
    void counter() const;

    virtual gl::GLenum objectType() const override;

protected:

    Query(std::unique_ptr<IDResource> && resource);

    void counter(gl::GLenum target) const;
};


} // namespace globjects
