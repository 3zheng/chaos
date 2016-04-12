CREATE PROCEDURE [dbo].[set_user_join_times]
	@user_id bigint,
	@today_join_times int,
	@total_join_times int,
	@join_date int,
	@plan_id int,
	@game_kind int
AS
--更新用户参赛次数
	update user_join_times set today_join_times = @today_join_times, total_join_times = @total_join_times, join_date = @join_date 
	where user_id = @user_id and plan_id = @plan_id and game_kind = @game_kind

	if @@ROWCOUNT = 0
	begin
		insert into user_join_times(user_id, today_join_times, total_join_times,  join_date, plan_id, game_kind)
			values(@user_id, @total_join_times, @total_join_times, @join_date, @plan_id, @game_kind)
	end
RETURN 0
