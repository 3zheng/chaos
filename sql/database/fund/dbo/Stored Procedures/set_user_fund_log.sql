CREATE PROCEDURE [dbo].[set_user_fund_log]
	@user_id bigint ,
	@fund_id int ,
	@change_count bigint ,
	@old_count bigint,
	@current_count bigint ,
	@reason_type int ,
	@reason_att_id int, 
	@att_content varchar(100),
	@app_type int,
	@app_id int,
	@fund_status int,
	@db_session_id bigint
AS
	SET NOCOUNT ON
	if @fund_status = 1
	begin
		insert into user_fund_log(user_id,  fund_id,  change_count,  old_count,  current_count,  reason_type,  reason_att_id,  att_content,  app_type,  app_id,  r_create_time, fund_status, db_session_id)
					   values(@user_id, @fund_id, @change_count, @old_count, @current_count, @reason_type, @reason_att_id, @att_content, @app_type, @app_id, getdate(), @fund_status, @db_session_id);
	end
	else if @fund_status = 2
	begin
		update user_fund_log set fund_status = 2 where db_session_id = @db_session_id;
	end
RETURN 0
