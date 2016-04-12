CREATE PROCEDURE [dbo].[get_user_game_result]
	@user_id bigint
AS
--取用户某个游戏的胜负局数
	SELECT * from user_game_result where user_id = @user_id;
RETURN 0
