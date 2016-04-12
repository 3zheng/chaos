CREATE PROCEDURE [dbo].[set_user_game_reslut]
	@user_id bigint,
	@win_times int,
	@draw_times int,
	@lose_times int,
	@game_kind int
AS
--更新用户的胜负局信息，如果没有相关记录则新建一条表记录
	update user_game_result set win_times = @win_times, draw_times = @draw_times, lose_times = @lose_times 
	where user_id = @user_id and game_kind = @game_kind
	if @@ROWCOUNT = 0
	begin
		insert into user_game_result(user_id, win_times, draw_times, lose_times, game_kind)
			values(@user_id, @win_times, @draw_times, @lose_times, @game_kind)
	end
RETURN 0
