#ifndef FG_RENDER_TASK_BASE_HPP_
#define FG_RENDER_TASK_BASE_HPP_

#include <string>
#include <vector>

namespace fg
{
class framegraph;
class render_task_builder;
class resource_base;

class render_task_base
{
public:
  explicit render_task_base  (const std::string& name) : name_(name), cull_immunity_(false)
  {
    
  }
  render_task_base           (const render_task_base&  that) = delete ;
  render_task_base           (      render_task_base&& temp) = default;
  virtual ~render_task_base  ()                              = default;
  render_task_base& operator=(const render_task_base&  that) = delete ;
  render_task_base& operator=(      render_task_base&& temp) = default;

  const std::string& name             () const
  {
    return name_;
  }
  void               set_name         (const std::string& name)
  {
    name_ = name;
  }
  
  bool               cull_immunity    () const
  {
    return cull_immunity_;
  }
  void               set_cull_immunity(const bool cull_immunity)
  {
    cull_immunity_ = cull_immunity;
  }

protected:
  friend framegraph;
  friend render_task_builder;

  virtual void setup  (render_task_builder& builder)       = 0;
  virtual void execute()                             const = 0;

  std::string                       name_         ;
  bool                              cull_immunity_;
  std::vector<const resource_base*> creates_      ;
  std::vector<const resource_base*> reads_        ;
  std::vector<const resource_base*> writes_       ;
};
}

#endif