CREATE PROCEDURE [dbo].[get_user_ioin_times]
	@user_id bigint
AS
--获取用户的参赛次数
	SELECT * from user_join_times where user_id = @user_id;
RETURN 0
