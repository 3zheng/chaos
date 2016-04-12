CREATE PROCEDURE [dbo].[fund_is_user_exist]
	@user_id int,
	@flag int out
AS
	SET NOCOUNT ON;
	--flag返回1表示用户存在，返回0表示用户不存在
    EXEC [QPTreasureDBLink].QPGameUserDB.DBO.Game_Match_Is_user_exist @user_ID, @flag out
RETURN 0

