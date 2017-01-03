#pragma once
namespace xwebsocket
{
	class xserver
	{
	public:
		xserver(std::size_t io_threads = std::thread::hardware_concurrency())
			:proactor_pool_(io_threads)
		{
			
		}
		xserver &bind(std::string &ip, int port)
		{
			proactor_pool_.bind(ip, port);
			return *this;
		}
		xserver &regist_on_message()
		{

		}
		void start()
		{
			proactor_pool_.start();
		}
		void stop()
		{
			proactor_pool_.stop();
		}
		
	private:
		void accept_callback(xnet::connection &&conn)
		{
			session sess(std::move(conn));
		}
		
		void add_session(session &&sess)
		{
			std::lock_guard<std::mutex> locker(session_mtx_);
			sess.id_ = session_id_;
			sessions_.emplace(session_id_, std::move(sess));
			++session_id_;
		}
		
		void del_session(int64_t id)
		{
			std::lock_guard<std::mutex> locker(session_mtx_);
			sessions_.erase(id);
		}

		std::mutex session_mtx_;
		int64_t session_id_ = 1;
		std::map<int64_t, session> sessions_;
		xnet::proactor_pool proactor_pool_;
	};
}