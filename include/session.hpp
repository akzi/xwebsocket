#pragma once
namespace xwebsocket
{
	class session
	{
	public:
		
		using frame_callback = frame_parser::frame_callback;

		session()
		{

		}

		session(session &&sess)
		{
			reset_move(std::move(sess));
		}

		session &operator=(session &&sess)
		{
			reset_move(std::move(sess));
			return *this;
		}

		void close()
		{
			assert(!is_close_);
			is_close_ = true;
		}
		void send_msg(std::string &&msg)
		{
			if (!is_send_)
				return do_send(std::move(msg));
			send_buffer_list_.emplace_back(std::move(msg));
		}
	private:
		friend class xserver;

		session(xnet::connection &&conn)
			:conn_(std::move(conn))
		{

		}

		void reset_move(session &&other)
		{
			if (&other == this)
				return;
			is_send_ = other.is_send_;
			is_close_ = other.is_close_;
			in_callback_ = other.in_callback_;
			id_ = other.id_;
			send_buffer_list_ = std::move(other.send_buffer_list_);
			close_callback_ = std::move(other.close_callback_);
			frame_parser_ = std::move(other.frame_parser_);
			conn_ = std::move(conn_);
		}
		session &regist_frame_callback(const frame_callback &callback)
		{
			frame_parser_.regist_frame_callback(callback);
			return *this;
		}
		void do_send(std::string &&buffer)
		{
			assert(!is_send_);
			conn_.async_send(std::move(buffer));
			is_send_ = true;
		}
		void init()
		{
			using namespace std::placeholders;
			conn_
				.regist_recv_callback(std::bind(&session::recv_callback, this, _1, _2))
				.regist_send_callback(std::bind(&session::send_callback, this, _1))
				.async_recv_some();
		}
		void recv_callback(char *data, std::size_t len)
		{
			if (len == 0)
			{
				on_close();
				return;
			}
			frame_parser_.do_parse(data, (uint32_t)len);
			conn_.async_recv_some();
		}
		void send_callback(std::size_t len)
		{
			is_send_ = false;
			if (len == 0)
			{
				on_close();
				return;
			}
			if (is_close_)
			{
				if (send_buffer_list_.empty() &&
					in_callback_ == false)
				{
					conn_.close();
					return;
				}
			}
			if (send_buffer_list_.empty())
				return;
			do_send(std::move(send_buffer_list_.front()));
			send_buffer_list_.pop_front();
		}
		
		void on_close()
		{
			if (close_callback_)
				close_callback_();
			conn_.close();
			delete this;
		}

		bool is_send_ = false;
		bool is_close_ = false;
		bool in_callback_ = false;
		int64_t id_ = 0;
		std::list<std::string> send_buffer_list_;
		std::function<void()> close_callback_;
		frame_parser frame_parser_;
		xnet::connection conn_;
	};
}